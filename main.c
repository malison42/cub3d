#include "cub.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nEnter map filename", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	if (ft_strcmp(&argv[1][ft_strlen(argv[1] - 4)], ".cub"))
	{
		ft_putstr_fd("Error\n"
			"File has to be with the .cub extension", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	parse_map(argv[1]);

	return (EXIT_SUCCESS);
}