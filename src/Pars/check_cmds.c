#include "../../inc/pipex.h"

char	*find_cmd_path(char *cmd, char **env_paths)
{
	char	*part_path;
	char	*cmd_path;
	int		i;

	if (!env_paths)
		return (NULL);
	i = 0;
	while (env_paths[i])
	{
		part_path = ft_strjoin(env_paths[i], "/");
		cmd_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char **get_env_paths(char **envp)
{
    char *path_var = NULL;
    char **paths = NULL;
    int i = 0;

    // Trouver la variable PATH dans l'environnement
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_var = envp[i] + 5; // Sauter "PATH="
            break;
        }
        i++;
    }

    // Si PATH n'est pas trouvé, retourner NULL
    if (!path_var)
        return (NULL);

    // Diviser PATH en chemins individuels
    paths = ft_split(path_var, ':');

    return (paths);
}

