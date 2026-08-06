/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:16:50 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/06 17:41:10 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	sim->start = 0;
	sim->start_time = get_time_ms();
	if (pthread_mutex_init(&sim->print_mutex, NULL))
		return (error("Failed to initialize print mutex."));
	sim->simulation_over = 0;
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
		if (pthread_mutex_init(&sim->dongles[i].mutex, NULL) != 0)
			return (error("Failed to initialize dongle mutex."));
		sim->dongles[i].state = AVAILABLE;
		sim->dongles[i].cooldown_start = 0;
		i++;
	}
	return (0);
}