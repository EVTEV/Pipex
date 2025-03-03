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

void free_pipex(t_pipex *pipex)
{
    int i;

    // Libérer la cmd1
    if (pipex->cmd1_args)
    {
        i = 0;
        while (pipex->cmd1_args[i])
            free(pipex->cmd1_args[i++]);
        free(pipex->cmd1_args);
    }

    // Libérer la cmd2
    if (pipex->cmd2_args)
    {
        i = 0;
        while (pipex->cmd2_args[i])
            free(pipex->cmd2_args[i++]);
        free(pipex->cmd2_args);
    }

    // Libérer les chemins
    if (pipex->cmd1_path)
        free(pipex->cmd1_path);
    if (pipex->cmd2_path)
        free(pipex->cmd2_path);
}

void free_env_paths(char **env_paths)
{
    int i;

    if (!env_paths)
        return;
    
    i = 0;
    while (env_paths[i])
        free(env_paths[i++]);
    free(env_paths);
}

