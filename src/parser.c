/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:21:52 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/06 18:21:52 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse_arguments(int argc, char **argv, t_sim *sim)
{
	validate_arguments(argc, argv);
	if (fill_simulation(argv, sim))
		return (1);
	return (0);
}
