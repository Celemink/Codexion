/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:44:13 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 17:36:17 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	pthread_mutex_lock(&sim->simulation_mutex);
	while (!sim->start)
	{
		pthread_mutex_unlock(&sim->simulation_mutex);
		precise_sleep(1);
		pthread_mutex_lock(&sim->simulation_mutex);
	}
	pthread_mutex_unlock(&sim->simulation_mutex);
	while (!simulation_is_over(sim))
	{
		i = 0;
		while (i < sim->number_of_coders)
		{
			if (!is_coder_burned_out(&sim->coders[i])
				&& check_coder_burnout(&sim->coders[i]))
			{
				set_coder_burned_out(&sim->coders[i]);
				log_action(&sim->coders[i], "\033[0;31mburned out\033[0m");
				set_simulation_over(sim);
				break ;
			}
			i++;
		}
		precise_sleep(1);
	}
	return (NULL);
}

int	check_coder_burnout(t_coder *coder)
{
	long	now;
	long	last;

	if (get_compile_counter(coder) == 0)
		return (0);
	now = time_since_start(coder->general_ref);
	last = get_last_compilation_time(coder);
	if (now - last >= coder->general_ref->time_to_burnout)
		return (1);
	return (0);
}
