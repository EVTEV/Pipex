#include "inc/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	ft_memset(&pipex, 0, sizeof(t_pipex));
	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	return (my_exec(&pipex, av, envp));
}
