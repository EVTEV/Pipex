#include "inc/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		exit_code;

	check_args(ac);
	check_infile(av[1]);
	init_pipex(&pipex, envp);
	exit_code = my_exec(&pipex, av, envp);
	free_pipex(&pipex);
	return (exit_code);
}
