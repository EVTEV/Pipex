#include "../../inc/pipex.h"

int	my_exec(t_pipex *pipex, char **av, char **envp)
{
	int	value;

	pipex->env_path = get_env_path(envp);
	if (init_command(pipex, av) != 0)
	{
		free_env_path(pipex->env_path);
		return (1);
	}
	value = exec_command(pipex, envp);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	free_pipex(pipex);
	free_env_path(pipex->env_path);
	if (pipex->permission)
		return (1);
	return (value);
}
