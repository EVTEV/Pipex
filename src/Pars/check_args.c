#include "../../inc/pipex.h"

int	check_args(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (1);
	}
	return (0);
}

int	check_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (1);
	}
	close(fd);
	return (0);
}
