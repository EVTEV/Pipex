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
