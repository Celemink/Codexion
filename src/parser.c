#include "codexion.h"

int	parse_arguments(int argc, char **argv, t_sim *sim)
{
	if (argc != 9)
		return(1);
	else
	{
		sim->number_of_coders = ft_atoi(argv[1]);
		sim->time_to_burnout = ft_atoi(argv[2]);
		sim->time_to_compile = ft_atoi(argv[3]);
		sim->time_to_debug = ft_atoi(argv[4]);
		sim->time_to_refactor = ft_atoi(argv[5]);
		sim->number_of_compiles_required = ft_atoi(argv[6]);
		sim->dongle_cooldown = ft_atoi(argv[7]);
		return (0);
	}
}