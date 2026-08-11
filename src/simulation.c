/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:17:45 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 18:15:05 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	start_simulation(t_sim *sim)
{
	sim->start_time = get_time_ms();
	if (pthread_create(&sim->monitor_thread, NULL,
			monitor_routine, sim) != 0)
		return (error("Failed to create monitor thread."));
	if (start_coder_threads(sim))
		return (1);
	pthread_mutex_lock(&sim->simulation_mutex);
	sim->start = 1;
	pthread_mutex_unlock(&sim->simulation_mutex);
	join_coder_threads(sim);
	pthread_join(sim->monitor_thread, NULL);
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

void	set_simulation_over(t_sim *sim)
{
	pthread_mutex_lock(&sim->simulation_mutex);
	sim->simulation_over = 1;
	pthread_mutex_unlock(&sim->simulation_mutex);
}
