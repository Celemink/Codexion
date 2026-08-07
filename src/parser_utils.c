/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:44:21 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/07 15:44:26 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse_scheduler(char *arg, t_scheduler *scheduler)
{
	if (!ft_strcmp(arg, "fifo"))
		*scheduler = FIFO;
	else if (!ft_strcmp(arg, "edf"))
		*scheduler = EDF;
	else
		return (error("Scheduler must be 'fifo' or 'edf'"));
	return (0);
}

int	fill_simulation(char **argv, t_sim *sim)
{
	sim->number_of_coders = ft_atol(argv[1]);
	sim->time_to_burnout = ft_atol(argv[2]);
	sim->time_to_compile = ft_atol(argv[3]);
	sim->time_to_debug = ft_atol(argv[4]);
	sim->time_to_refactor = ft_atol(argv[5]);
	sim->number_of_compiles_required = ft_atol(argv[6]);
	sim->dongle_cooldown = ft_atol(argv[7]);
	if (parse_scheduler(argv[8], &sim->scheduler))
		return (1);
	return (0);
}

int error(char *message)
{
	write(2, "ERROR: ", 7);
	ft_putendl_fd(message, 2);
	return (1);
}

int	is_positive_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (NOT_NUMERIC);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (NEGATIVE);
		i++;
	}
	if (!str[i])
		return (NOT_NUMERIC);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (NOT_NUMERIC);
		i++;
	}
	return (VALID);
}

int	validate_arguments(int argc, char **argv)
{
	int	i;
	int	result;

	i = 1;
	if (argc != 9)
		return (error("Invalid number of arguments"));
	while (i < 8)
	{
		result = is_positive_number(argv[i]);
		if (result == NOT_NUMERIC)
			return (error("Arguments must be numeric."));
		if (result == NEGATIVE)
			return (error("Arguments must be positive."));
		i++;
	}
	return (0);
}