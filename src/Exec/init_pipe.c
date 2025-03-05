/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:57:12 by acaes             #+#    #+#             */
/*   Updated: 2025/03/05 14:57:12 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		pipex->env_path = NULL;
	else
		pipex->env_path = ft_split(envp[i] + 5, ':');
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->cmd1_args)
	{
		i = 0;
		while (pipex->cmd1_args[i])
			free(pipex->cmd1_args[i++]);
		free(pipex->cmd1_args);
	}
	if (pipex->cmd2_args)
	{
		i = 0;
		while (pipex->cmd2_args[i])
			free(pipex->cmd2_args[i++]);
		free(pipex->cmd2_args);
	}
	if (pipex->cmd1_path)
		free(pipex->cmd1_path);
	if (pipex->cmd2_path)
		free(pipex->cmd2_path);
}

void	free_env_path(char **env_path)
{
	int	i;

	if (!env_path)
		return ;
	i = 0;
	while (env_path[i])
		free(env_path[i++]);
	free(env_path);
}
