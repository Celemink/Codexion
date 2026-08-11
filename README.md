*This project has been created as part of the 42 curriculum by `lodazzan`.*

## ⚠️ Disclaimer

- **Full Portfolio:** This repository focuses on this specific project. You can find my entire portfolio 👉 [here](https://github.com/Celemink).
- **Subject Rules:** I strictly follow the rules regarding 42 subjects; I cannot share the PDFs, but I explain the concepts in this README.
- **Archive State:** The code is preserved exactly as it was during evaluation (graded state). I do not update it, so you can see my progress and mistakes from that time.
- **Academic Integrity:** I encourage you to try the project yourself first. Use this repo only as a reference, not for copy-pasting. Be patient, you will succeed.


# Codexion

## Description

Codexion is a concurrency and multithreading project developed as part of the 42 curriculum.

The project simulates a group of coders competing for a limited number of shared resources called **dongles**. Each coder must acquire the two dongles associated with them before being able to compile. After compiling, the coder performs debugging and refactoring before attempting to compile again.

The main goal of the project is to implement this simulation safely using POSIX threads while handling the synchronization problems that arise when multiple threads compete for the same resources.

The simulation also includes a scheduler that determines which waiting coder should be given priority when several coders are requesting dongles.

Two scheduling policies are supported:

* **FIFO** — First In, First Out. The coder whose request started waiting first receives priority.
* **EDF** — Earliest Deadline First. Priority is based on the coder's deadline, calculated from the beginning of their last compilation and the configured burnout time.

The program also monitors coders continuously so that a coder that exceeds their allowed time without compiling is detected as precisely as possible.

## Features

* Multiple coder threads running concurrently.
* Shared dongle resources protected with mutexes.
* FIFO scheduling.
* Earliest Deadline First (EDF) scheduling.
* Dongle cooldown handling.
* Coder burnout detection.
* Serialized simulation logging.
* Thread-safe simulation termination.
* Support for a single coder and multiple coders.
* Protection against deadlocks when acquiring two dongles.
* Synchronization between coder threads and the monitor thread.
* Thread-safe access to scheduler state.

## Instructions

### Compilation

The project is compiled using the provided `Makefile`.

Run:

```bash
make
```

To remove object files:

```bash
make clean
```

To remove all generated compilation files and the executable:

```bash
make fclean
```

To rebuild the project from scratch:

```bash
make re
```

### Execution

The program is executed with the following arguments:

```text
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

The scheduler must be one of:

```text
fifo
edf
```

For example:

```bash
./codexion 20 70 70 70 70 70 70 edf
```

This starts a simulation with:

* 20 coders
* 70 ms until burnout
* 70 ms compilation time
* 70 ms debugging time
* 70 ms refactoring time
* 70 required compilations
* 70 ms dongle cooldown
* EDF scheduling

The program prints timestamped actions to the terminal, allowing the progress of the simulation and coder states to be observed.

## Blocking cases handled

The project addresses several concurrency problems that can occur when multiple threads compete for shared dongles.

### Deadlock prevention

A coder requires two dongles to compile. If multiple coders acquire one dongle each and then wait indefinitely for their second dongle, a deadlock can occur.

The implementation therefore handles the two-dongle acquisition as an operation that must either obtain both resources or release the first dongle when the second one cannot be obtained.

This prevents a coder from permanently holding one dongle while waiting for another.

The solution also considers the Coffman conditions associated with deadlocks, particularly the circular-wait situation created when several coders hold one resource while waiting for another.

### Starvation prevention

The scheduler prevents a coder from being ignored indefinitely when other coders repeatedly obtain the available dongles.

With FIFO scheduling, waiting priority is determined by the time at which the coder started waiting.

With EDF scheduling, waiting coders are compared according to their compilation deadlines. This allows the scheduler to prioritize coders that are closer to their burnout deadline.

### Cooldown handling

After a dongle is released, it enters a cooldown state before becoming available again.

The dongle state is protected by its mutex. A coder can only use a dongle when it is available or when its cooldown period has elapsed.

This prevents multiple threads from simultaneously treating the same dongle as available.

### Precise burnout detection

The monitor thread continuously checks the coders and determines whether a coder has exceeded the configured burnout time since their last compilation.

Time measurements use millisecond timestamps so that burnout detection can be performed independently from the coder threads.

Once burnout is detected, the simulation can be marked as finished and the other threads can terminate.

### Log serialization

Multiple coder threads can attempt to print messages simultaneously.

Logging is therefore synchronized so that messages from different threads do not corrupt each other or become interleaved.

This keeps each simulation event readable and provides a consistent terminal output.

## Thread synchronization mechanisms

The project uses POSIX threads and mutexes to coordinate access to shared state.

### `pthread_mutex_t`

`pthread_mutex_t` is the primary synchronization primitive used by the project.

Mutexes protect shared resources and state from simultaneous access by multiple threads.

#### Dongles

Each dongle has its own mutex:

```c
typedef struct s_dongle
{
    pthread_mutex_t     mutex;
    t_dongle_state      state;
    long                cooldown_start;
}   t_dongle;
```

When a coder attempts to take a dongle, its mutex is locked before checking or changing its state.

This prevents two coder threads from simultaneously acquiring the same dongle.

Conceptually:

```c
pthread_mutex_lock(&dongle->mutex);

if (dongle_ready(dongle, cooldown))
{
    dongle->state = IN_USE;
    success = 1;
}

pthread_mutex_unlock(&dongle->mutex);
```

The same mutex protects the transition back to the cooldown state when a dongle is released.

### Scheduler state

The scheduler has its own mutex:

```c
pthread_mutex_t scheduler_mutex;
```

This protects scheduler-related shared information, such as when a coder begins or stops waiting.

For example, the waiting timestamp is updated while holding the scheduler mutex so that other coder threads cannot observe an inconsistent scheduler state.

### Simulation state

The simulation contains a mutex used to protect shared simulation state:

```c
pthread_mutex_t simulation_mutex;
```

This is used for state such as the simulation start and termination status.

This prevents coder threads and the monitor thread from racing when reading or modifying the simulation state.

### Logging

A dedicated print mutex is used to serialize output:

```c
pthread_mutex_t print_mutex;
```

When a thread logs an action, it acquires this mutex before printing and releases it afterwards.

Without this protection, several coder threads could write to the terminal simultaneously.

### Thread-safe communication between coders and the monitor

The simulation contains a dedicated monitor thread responsible for checking coder burnout.

The coder threads update their state as they compile and perform their other activities. The monitor reads this shared state while synchronization mechanisms protect accesses that can occur concurrently.

When the monitor detects a burnout condition, it updates the shared simulation termination state. Coder threads check that state and stop their work when the simulation has ended.

This creates a synchronized communication path between the monitor and the coder threads without requiring the threads to directly manipulate each other's execution.

### Condition variables and custom events

The current implementation does not rely on `pthread_cond_t` or a separate custom event abstraction for the core scheduling mechanism. Synchronization is performed through the mutexes and the shared simulation/scheduler state already present in the project.

If a future version introduces condition variables or a custom event system, those mechanisms could be used to allow threads to sleep until a relevant state change instead of repeatedly checking shared state.

## Scheduling

### FIFO

FIFO stands for **First In, First Out**.

When multiple coders are waiting for dongles, the coder that began waiting first has priority.

The implementation records when a coder starts waiting and compares that timestamp against the waiting timestamps of the other coders.

### EDF

EDF stands for **Earliest Deadline First**.

Each coder has a deadline calculated from their last compilation start time and the configured burnout period:

```text
deadline = last_compile_start + time_to_burnout
```

The scheduler compares the deadlines of waiting coders and gives priority to the coder with the earliest relevant deadline.

This is particularly important because allowing a coder with an imminent burnout deadline to remain blocked behind other coders could cause unnecessary burnout.

## Dongle states

Each dongle can be in one of three states:

```text
AVAILABLE
IN_USE
COOLDOWN
```

* **AVAILABLE** — a coder can acquire the dongle.
* **IN_USE** — the dongle is currently held by a coder.
* **COOLDOWN** — the dongle has been released but must wait for the configured cooldown period before becoming available again.

## Resources

The project was developed using the following types of resources:

* **POSIX Threads documentation** — reference for `pthread_create`, `pthread_join`, `pthread_mutex_t`, mutex locking and thread synchronization.
* **Linux `pthread` documentation** — reference for the behavior of POSIX threading primitives.
* **Valgrind Helgrind documentation** — used to detect potential data races, incorrect mutex usage and other thread synchronization problems.
* **42 curriculum documentation and project subject** — used as the primary specification for the required behavior and constraints of Codexion.
* **Operating Systems / concurrency resources** — used to understand deadlocks, race conditions, starvation, mutual exclusion and resource scheduling.

### AI usage

AI assistance was used during the development of this project as a programming support and debugging tool.

It was used for:

* Understanding and reviewing the concurrency requirements.
* Discussing possible implementations of FIFO and EDF scheduling.
* Reviewing the interaction between coder threads and shared dongles.
* Identifying potential race conditions and synchronization problems.
* Interpreting and debugging Helgrind output.
* Reviewing mutex usage and shared-state access.
* Helping identify deadlock and starvation scenarios.
* Reviewing functions for correctness and helping keep the implementation within the project's function-size constraints.
* Explaining compiler errors and warnings.
* Reviewing code provided by the project author and suggesting targeted modifications.
* Helping structure and document the final README.

The implementation and final decisions were made by the project author. AI was used as an assistant for reasoning, debugging, explanation and documentation rather than as a replacement for understanding or testing the code.

## Project structure

The project is organized around the main components of the simulation:

```text
Codexion/
├── Makefile
├── README.md
├── include/
│   └── codexion.h
└── src/
    ├── ...
    ├── scheduler/
    │   └── ...
    └── ...
```

The exact source-file organization may vary according to the final version of the project.

## Testing

The program can be tested with different numbers of coders and different scheduler configurations.

Example:

```bash
./codexion 1 70 70 70 70 70 70 fifo
```

and:

```bash
./codexion 20 70 70 70 70 70 70 edf
```

Thread-safety testing can be performed with Helgrind:

```bash
valgrind --tool=helgrind ./codexion 20 70 70 70 70 70 70 edf
```

Testing different coder counts is particularly useful for exposing synchronization problems, resource contention, starvation and termination issues.
