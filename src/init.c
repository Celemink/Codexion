#include "codexion.h"

int	init_simulation(t_sim *sim)
{
	if (init_coders(sim))
		return (1);
	if (init_dongles(sim))
	{
		free_simulation(sim);
		return (1);
	}
	return (0);
}

int init_coders(t_sim *sim)
{
	int	i;

	i = 0;
	sim->coders = malloc(sizeof(t_coder) * sim->number_of_coders);
	if (!sim->coders)
		return (error("Failed to allocate coders."));
	while (i < sim->number_of_coders)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].compile_counter = 0;
		sim->coders[i].compile_timer = 0;
		sim->coders[i].last_compilation_timer = 0;
		sim->coders[i].general_ref = sim;
		if (pthread_mutex_init(&sim->coders[i].state_mutex, NULL) != 0)
			return (error("Failed to initialize coder mutex."));
		i++;
	}
	return (0);
}

int	init_dongles(t_sim *sim)
{
	int	i;

	sim->dongles = malloc(sizeof(t_dongle) * sim->number_of_coders);
	if (!sim->dongles)
		return (error("Failed to allocate dongles."));
	i = 0;
	while (i < sim->number_of_coders)
	{
		sim->dongles[i].state = AVAILABLE;
		sim->dongles[i].state_timer = 0;
		if (pthread_mutex_init(&sim->dongles[i].mutex, NULL) != 0)
			return (error("Failed to initialize dongle mutex."));
		i++;
	}
	return (0);
}

void	free_simulation(t_sim *sim)
{
	int	i;

	if (sim->coders)
	{
		i = 0;
		while (i < sim->number_of_coders)
		{
			pthread_mutex_destroy(&sim->coders[i].state_mutex);
			i++;
		}
		free(sim->coders);
	}
	if (sim->dongles)
	{
		i = 0;
		while (i < sim->number_of_coders)
		{
			pthread_mutex_destroy(&sim->dongles[i].mutex);
			i++;
		}
		free(sim->dongles);
	}
}