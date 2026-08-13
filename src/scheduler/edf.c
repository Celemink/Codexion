/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:22 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/13 12:57:50 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_edf_priority(t_coder *coder, t_sim *sim,
		long deadline, long now)
{
	int		i;
	long	others_deadline;

	i = 0;
	while (i < sim->number_of_coders)
	{
		if (sim->coders[i].waiting_since > 0
			&& sim->coders[i].id != coder->id)
		{
			others_deadline = sim->coders[i].last_compilation_timer
				+ sim->time_to_burnout;
			if (others_deadline < deadline && others_deadline > now)
				return (0);
		}
		i++;
	}
	return (1);
}

int	edf_has_priority(t_coder *coder)
{
	t_sim	*sim;
	long	now;
	long	deadline;
	int		result;

	sim = coder->general_ref;
	now = time_since_start(sim);
	deadline = coder->last_compilation_timer + sim->time_to_burnout;
	pthread_mutex_lock(&sim->scheduler_mutex);
	result = check_edf_priority(coder, sim, deadline, now);
	pthread_mutex_unlock(&sim->scheduler_mutex);
	return (result);
}
