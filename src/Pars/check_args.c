#include "../../inc/pipex.h"

int	check_args(int ac)
{
	if (ac != 5)
		return (p_error("Error\n Invalid number of arguments\n"));
	return (0);
}

int	check_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		return (p_error("Error\n Invalid infile\n"));
	close(fd);
	return (0);
}
