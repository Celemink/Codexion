/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:17:45 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/10 17:29:31 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	start_simulation(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_coders)
	{
		if (pthread_create(&sim->coders[i].thread,
				NULL,
				coder_routine,
				&sim->coders[i]) != 0)
			return (error("Failed to create thread."));
		i++;
	}
	sim->start_time = get_time_ms();
	sim->start = 1;
	i = 0;
	while (i < sim->number_of_coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}	
	return (0);
}

int	all_coders_finished(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_coders)
	{
		if (get_compile_counter(&sim->coders[i])
			< sim->number_of_compiles_required)
			return (0);
		i++;
	}
	return (1);
}

int	simulation_is_over(t_sim *sim)
{
	int	result;

	pthread_mutex_lock(&sim->simulation_mutex);
	result = sim->simulation_over;
	pthread_mutex_unlock(&sim->simulation_mutex);
	return (result);
}

void	set_simulation_over(t_sim *sim)   //pienso que esto es useless MIRAR INIT.C
{
	pthread_mutex_lock(&sim->simulation_mutex);
	sim->simulation_over = 1;
	pthread_mutex_unlock(&sim->simulation_mutex);
}