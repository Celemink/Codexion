/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:55 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 18:42:47 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_action(t_coder *coder, char *action)
{
	long	time;
	t_sim	*sim;

	sim = coder->general_ref;
	pthread_mutex_lock(&coder->general_ref->print_mutex);
	time = get_time_ms() - coder->general_ref->start_time;
	if (simulation_is_over(sim) == 1)
	{
		pthread_mutex_unlock(&coder->general_ref->print_mutex);
		return ;
	}
	printf("%ld coder %d %s\n", time, coder->id, action);
	pthread_mutex_unlock(&coder->general_ref->print_mutex);
}
