#include "inc/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		exit_code;

	if (ac != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	init_pipex(&pipex, envp);
	exit_code = my_exec(&pipex, av, envp);
	free_pipex(&pipex);
	return (exit_code);
}
