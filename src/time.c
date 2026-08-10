/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:17:15 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/10 17:39:21 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(long duration_ms)
{
	long	start;

	start = get_time_ms();
	while(get_time_ms() - start < duration_ms)
		usleep(500);
}

long	time_since_start(t_sim *sim)
{
	return (get_time_ms() - sim->start_time);
}