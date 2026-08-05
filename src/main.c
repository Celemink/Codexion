#include "codexion.h"

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (parse_arguments(argc, argv, &sim))
		return (1);
	if (init_simulation(&sim))
		return (1);
	write(1, "bien cele", 9);
	return (0);
}
