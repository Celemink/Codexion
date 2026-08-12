/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:44:08 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/07 15:44:08 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_sim	sim;
	t_heap	heap;

	if (parse_arguments(argc, argv, &sim))
		return (1);
	if (init_simulation(&sim) || heap_init(&heap, sim.number_of_coders))
		return (1);
	if (start_simulation(&sim))
	{
		free_simulation(&sim);
		return (1);
	}
	free_simulation(&sim);
	return (0);
}
