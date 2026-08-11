/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:47:16 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 11:53:58 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	has_scheduler_priority(t_coder *coder)
{
	if (coder->general_ref->scheduler == FIFO)
		return (edf_has_priority(coder));
	if (coder->general_ref->scheduler == EDF)
		return (fifo_has_priority(coder));
	return (0);
}