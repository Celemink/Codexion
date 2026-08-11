/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:07 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/07 15:43:07 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define VALID			1
# define NOT_NUMERIC	0
# define NEGATIVE		-1

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_sim		t_sim;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_heap
{
	t_coder	**coders;
	int		size;
	int		capacity;
}			t_heap;

typedef enum e_dongle_state
{
	AVAILABLE,
	IN_USE,
	COOLDOWN
}	t_dongle_state;

typedef struct s_dongle
{
	pthread_mutex_t		mutex;
	t_dongle_state		state;
	long				cooldown_start;
}						t_dongle;

typedef struct s_sim
{
	int				number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	int				number_of_compiles_required;
	long			dongle_cooldown;
	t_scheduler		scheduler;

	t_dongle		*dongles;
	t_coder			*coders;

	pthread_t		monitor_thread;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	scheduler_mutex;

	long			start_time;
	int				start;
	int				simulation_over;
}					t_sim;

typedef struct s_coder
{
	int					id;
	int					compile_counter;
	long				compile_timer;
	long				last_compilation_timer;
	long				waiting_since;

	pthread_t			thread;
	pthread_mutex_t		state_mutex;

	t_sim				*general_ref;

	int					left_dongle;
	int					right_dongle;

	int					burned_out;
}						t_coder;

int		parse_arguments(int argc, char **argv, t_sim *sim);

int		take_dongle(t_dongle *dongle, long cooldown);
void	release_dongle(t_dongle *dongle);
int		take_both_dongles(t_coder *coder);
void	release_both_dongles(t_coder *coder);
int		dongle_ready(t_dongle *dongle, long cooldown);

int		validate_arguments(int argc, char **argv);
int		fill_simulation(char **argv, t_sim *sim);

void	compile(t_coder *coder);
void	debug(t_coder *coder);
void	refactor(t_coder *coder);

int		parse_scheduler(char *arg, t_scheduler *scheduler);
int		is_positive_number(char *str);

int		error(char *message);

long	ft_atol(const char *str);
void	ft_putendl_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);

int		init_simulation(t_sim *sim);

int		init_coders(t_sim *sim);
int		init_dongles(t_sim *sim);
int		init_scheduler(t_sim *sim);
int		fifo_has_priority(t_coder *coder);
void	fifo_start_waiting(t_coder *coder);

void	simulation_finisher(t_coder *coder);
void	log_action(t_coder *coder, char *action);

void	free_simulation(t_sim *sim);

long	get_time_ms(void);
void	precise_sleep(long duration_ms);

void	*coder_routine(void *arg);

int		start_simulation(t_sim *sim);
int		all_coders_finished(t_sim *sim);

int		simulation_is_over(t_sim *sim);
void	set_simulation_over(t_sim *sim);

int		get_compile_counter(t_coder *coder);
long	get_last_compilation_time(t_coder *coder);

long	time_since_start(t_sim *sim);

void	*monitor_routine(void *arg);
int		check_coder_burnout(t_coder *coder);

int		is_coder_burned_out(t_coder *coder);
void	set_coder_burned_out(t_coder *coder);

int		has_scheduler_priority(t_coder *coder);
int		edf_has_priority(t_coder *coder);
long	coder_deadline(t_coder *coder);
void	swap_coders(t_coder **a, t_coder **b);

int		heap_init(t_heap *heap, int capacity);
void	heap_destroy(t_heap *heap);
int		heap_push(t_heap *heap, t_coder *coder);
t_coder	*heap_pop(t_heap *heap);
t_coder	*heap_check(t_heap *heap);
int		smallest_checker(int sample, t_heap *heap, int smallest);

int		start_coder_threads(t_sim *sim);
void	join_coder_threads(t_sim *sim);

#endif

//N threads = N filosofos (tantos threads como filosofos haya)

//· pthread_t - LA CAJA
//	Crea el hueco donde va a haber un thread

//· pthread_create - EL EJECUTOR
//	Pone a trabajar el hilo

//	PARÁMETROS QUE RECIBE
//	pthread_create(&hilo, NULL, funcion, argumento)
//		1- &HILO
//			Referencia al hilo ya creado
//		2- NULL
//			Modificadores de la función (no usado en Codexion)
//		3- FUNCION
//			El trabajo tiene que hacer el hilo
//		4- ARGUMENTO
//			Normalmente, la estructura del simulador general, o partes de él

//· pthread_mutex_t - EL SEMAFORO
//	Impide que varios hilos actuen en el mismo codigo a la vez

//	ESTRUCTURA
//	pthread_mutex_t nombre_del_mutex;

/*cada filosofo es un hilo de ejecución

compilar es comer, co

mutex recursos compartidos entre hilos

hilos com se inician

data race, race condition

josemi isallnum

usleep son microseguntos pero  me han pedido milisegundos

gettimeofday() DA EN SEGUNDOS desde 1970 epoch inicio de los tiempos para C*/





//HAY QUE HACER OPCION DE UN PHILOSOPHER PORQUE SOLO HAY UN PALILLO
//SE TIENE QUE PARAR LA EJECUCION SI UN FILOSOFO MUERE / 200 FILOSOFOS EJEMPLO
//TIENE QUE AVISAR DE CUANDO COGE UN DONGLE

//COGER TENEDOR Y ESPERAR A QUE MUERA EL FILOSOFO - CASI 1 FILOSOFO


//DUDAS:
//1- Al usar valgrind --tool=helgrind ./codexion 20 70 70 70 70 70 70 edf
//		se queda cogiendo el dongle infinitamente pero al probar el
//		comando de manera normal, no. Es eso un fallo o es culpa de helgrind?

//2- A veces cuando todo ocurre en el mismo segundo, hay prints debajo del burned out