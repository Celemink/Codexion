/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:18:22 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/06 17:10:06 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	int			i;

	coder = (t_coder *)arg;
	i = 0;
	while (i < 5)
	{
		log_action(coder, "is alive");
		precise_sleep(100);
		i++;
	}
	return (NULL);
}