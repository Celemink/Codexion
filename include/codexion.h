/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:23:52 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/06 17:23:52 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define VALID			1
# define NOT_NUMERIC		0
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

	long			start_time;

	pthread_mutex_t	print_mutex;

	int				start;
	int				simulation_over;
}					t_sim;

typedef struct s_coder
{
	int					id;
	int					compile_counter;
	long				compile_timer;
	long				last_compilation_timer;

	pthread_t			thread;
	pthread_mutex_t		state_mutex;

	t_sim				*general_ref;
}						t_coder;

int		parse_arguments(int argc, char **argv, t_sim *sim);

int		take_dongle(t_dongle *dongle);

int		validate_arguments(int argc, char **argv);
int		fill_simulation(char **argv, t_sim *sim);

int		parse_scheduler(char *arg, t_scheduler *scheduler);
int		is_number(char *str);

int		error(char *message);

long	ft_atol(const char *str);
void	ft_putendl_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);

int		init_simulation(t_sim *sim);

int		init_coders(t_sim *sim);
int		init_dongles(t_sim *sim);

void	log_action(t_coder *coder, char *action);

void	free_simulation(t_sim *sim);

long	get_time_ms(void);
void	precise_sleep(long duration_ms);

void	*coder_routine(void *arg);

int		start_simulation(t_sim *sim);

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