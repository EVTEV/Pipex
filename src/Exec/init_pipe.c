#include "../../inc/pipex.h"

void	init_pipex(t_pipex *pipex, char **envp)
{
	int	i;

	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->cmd1_args = NULL;
	pipex->cmd2_args = NULL;
	pipex->cmd1_path = NULL;
	pipex->cmd2_path = NULL;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		pipex->env_paths = NULL;
	else
		pipex->env_paths = ft_split(envp[i] + 5, ':');
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex->infile > 0)
		close(pipex->infile);
	if (pipex->outfile > 0)
		close(pipex->outfile);
	if (pipex->pipe_fd[0] > 0)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] > 0)
		close(pipex->pipe_fd[1]);
	if (pipex->cmd1_args)
		free_tab(pipex->cmd1_args);
	if (pipex->cmd2_args)
		free_tab(pipex->cmd2_args);
	if (pipex->cmd1_path)
		free(pipex->cmd1_path);
	if (pipex->cmd2_path)
		free(pipex->cmd2_path);
	if (pipex->env_paths)
		free_tab(pipex->env_paths);
}
