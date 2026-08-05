#ifndef CODEXION_H
# define CODEXION_H

#include <pthread.h>
# include <sys/time.h>

typedef struct s_sim		t_sim;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;

typedef struct s_dongle
{
	pthread_mutex	mutex;
	long			state_timer;
}					t_dongle;

typedef struct s_sim
{
	int			number_of_coders;    hola me llamo
	long		time_to_burnout;
	long		time_to_compile;
	long		time_to_debug;
	long		time_to_refactor;
	int			number_of_compiles_required;
	long		dongle_cooldown;
	char		scheduler[5];

	t_dongle	*dongles;
	t_coder		*coders;
}				t_sim;

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

int	parse_arguments(int argc, char **argv, t_sim *sim);

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