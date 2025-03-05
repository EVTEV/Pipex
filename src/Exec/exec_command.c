/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:56:47 by acaes             #+#    #+#             */
/*   Updated: 2025/03/05 14:56:47 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

static int	handle_child_processes(t_pipex *pipex, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
	{
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		return (p_error("Fork error"));
	}
	if (pipex->pid1 == 0)
		first_child(pipex, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
	{
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		waitpid(pipex->pid1, NULL, 0);
		return (p_error("Fork error"));
	}
	if (pipex->pid2 == 0)
		second_child(pipex, envp);
	return (0);
}

int	exec_command(t_pipex *pipex, char **envp)
{
	int	status1;
	int	status2;
	int	exit_status;

	if (pipe(pipex->pipe_fd) < 0)
		return (p_error("Pipe error"));
	if (handle_child_processes(pipex, envp) != 0)
		return (1);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->pid1, &status1, 0);
	waitpid(pipex->pid2, &status2, 0);
	if (WIFEXITED(status2))
		exit_status = WEXITSTATUS(status2);
	else
		exit_status = 1;
	return (exit_status);
}
