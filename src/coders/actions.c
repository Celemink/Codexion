/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:42:59 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/07 15:54:13 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compile(t_coder *coder)
{
	log_action(coder, "\033[0;33mis compiling\033[0m");
	coder->last_compilation_timer = get_time_ms();
	precise_sleep(coder->general_ref->time_to_compile);
	coder->compile_counter++;
	release_both_dongles(coder);
}