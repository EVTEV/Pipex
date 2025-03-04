#include "../../inc/pipex.h"

char	*find_cmd_path(char *cmd, char **env_path)
{
	char	*part_path;
	char	*cmd_path;
	int		i;

	if (!env_path)
		return (NULL);
	i = 0;
	while (env_path[i])
	{
		part_path = ft_strjoin(env_path[i], "/");
		cmd_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	**get_env_path(char **envp)
{
	char	*path_var;
	char	**path;
	int		i;

	path_var = NULL;
	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_var = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_var)
		return (NULL);
	path = ft_split(path_var, ':');
	return (path);
}
