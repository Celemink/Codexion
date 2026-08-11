/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:43:37 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 13:00:35 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	get_compile_counter(t_coder *coder)
{
	int	counter;

	pthread_mutex_lock(&coder->state_mutex);
	counter = coder->compile_counter;
	pthread_mutex_unlock(&coder->state_mutex);
	return (counter);
}

long	get_last_compilation_time(t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&coder->state_mutex);
	time = coder->last_compilation_timer;
	pthread_mutex_unlock(&coder->state_mutex);
	return (time);
}
