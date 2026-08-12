/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:42:59 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/12 17:05:12 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compile(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->general_ref;
	log_action(coder, "\033[0;32mis compiling\033[0m");
	pthread_mutex_lock(&coder->state_mutex);
	//coder->last_compilation_timer = time_since_start(coder->general_ref);
	pthread_mutex_unlock(&coder->state_mutex);
	precise_sleep(coder->general_ref->time_to_compile);
	pthread_mutex_lock(&coder->state_mutex);
	coder->compile_counter++;
	pthread_mutex_unlock(&coder->state_mutex);
	release_both_dongles(coder);
}

void	debug(t_coder *coder)
{
	long	debug_time;
	t_sim	*sim;

	sim = coder->general_ref;
	
	if (simulation_is_over(sim) == 1)
		return ;
	log_action(coder, "\033[0;33mis debugging\033[0m");
	pthread_mutex_lock(&coder->state_mutex);
	coder->last_compilation_timer = time_since_start(coder->general_ref);
	debug_time = coder->general_ref->time_to_debug;
	pthread_mutex_unlock(&coder->state_mutex);
	precise_sleep(debug_time);
}

void	refactor(t_coder *coder)
{
	long	refactor_time;
	t_sim	*sim;

	sim = coder->general_ref;
	
	if (simulation_is_over(sim) == 1)
		return ;
	log_action(coder, "\033[0;34mis refactoring\033[0m");
	pthread_mutex_lock(&coder->state_mutex);
	refactor_time = coder->general_ref->time_to_refactor;
	pthread_mutex_unlock(&coder->state_mutex);
	precise_sleep(refactor_time);
}
