/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:17:59 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/07 15:27:30 by lodazzan         ###   ########.fr       */
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

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->state = AVAILABLE;
	pthread_mutex_unlock(&dongle->mutex);
}

int	take_both_dongles(t_coder *coder) //version de laureano
{
	t_dongle *left;
	t_dongle *right;

	left = &coder->general_ref->dongles[coder->left_dongle];
	right = &coder->general_ref->dongles[coder->right_dongle];
	if (!take_dongle(left))
		return (0);
	if (!take_dongle(right))
	{
		release_dongle(left);
		return (0);
	}
	return (1);
}

void	release_both_dongles(t_coder *coder)
{
	t_dongle	*left;
	t_dongle	*right;

	left = &coder->general_ref->dongles[coder->left_dongle];
	right = &coder->general_ref->dongles[coder->right_dongle];
	release_dongle(left);
	release_dongle(right);
}