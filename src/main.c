#include "codexion.h"

int	parse_arguments(int argc, char **argv, t_sim *sim)
{
	if (argc != 9)
		return(1);
	else
	{
		(void)argv;
		(void)sim;
		return (0);
	}
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (parse_arguments(argc, argv, &sim))
		return (1);
	return (0);
}