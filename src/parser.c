#include "codexion.h"

int	parse_arguments(int argc, char **argv, t_sim *sim)
{
	validate_arguments(argc, argv);
	if (fill_simulation(argv, sim))
		return (1);
	return (0);
}
