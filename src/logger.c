/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:16:44 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/06 17:09:14 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//PONER COLORINCHIS A LOS MENSAJES

void	log_action(t_coder *coder, char *action)
{
	long	time;

	pthread_mutex_lock(&coder->general_ref->print_mutex);
	time = get_time_ms() - coder->general_ref->start_time;
	printf("%ld %d %s\n", time, coder->id, action);
	pthread_mutex_unlock(&coder->general_ref->print_mutex);
}