/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:17:59 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/06 18:22:13 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	take_dongle(t_dongle *dongle)
{
	int	success;

	success = 0;
	pthread_mutex_lock(&dongle->mutex);
	if (dongle->state == AVAILABLE)
	{
		dongle->state = IN_USE;
		success = 1;
	}
	pthread_mutex_unlock(&dongle->mutex);
	return (success);
}