#include "../../inc/pipex.h"

static void	setup_first_child(t_pipex *pipex)
{
	int	null_fd;

	if (pipex->infile >= 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) < 0)
			return (msg_error("dup2"));
	}
	else
	{
		null_fd = open("/dev/null", O_RDONLY);
		if (null_fd >= 0)
		{
			dup2(null_fd, STDIN_FILENO);
			close(null_fd);
		}
	}
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) < 0)
		return (msg_error("dup2"));
}

void	first_child(t_pipex *pipex, char **envp)
{
	setup_first_child(pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (!pipex->cmd1_path || !pipex->cmd1_args[0]
		|| pipex->cmd1_args[0][0] == '\0')
	{
		free_pipex(pipex);
		free_env_path(pipex->env_path);
		exit(0);
	}
	execve(pipex->cmd1_path, pipex->cmd1_args, envp);
	perror("execve");
	free_pipex(pipex);
	free_env_path(pipex->env_path);
	exit(127);
}

static void	setup_second_child(t_pipex *pipex)
{
	int null_fd;

	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) < 0)
		return (msg_error("dup2"));
	if (pipex->outfile >= 0)
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
			return (msg_error("dup2"));
	}
	else
	{
		null_fd = open("/dev/null", O_WRONLY);
		if (null_fd >= 0)
		{
			dup2(null_fd, STDOUT_FILENO);
			close(null_fd);
		}
	}
}

static void	handle_second_child_exit(t_pipex *pipex, char *cmd)
{
	if (cmd)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	free_pipex(pipex);
	free_env_path(pipex->env_path);
	exit(127);
}

void	second_child(t_pipex *pipex, char **envp)
{
	setup_second_child(pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (!pipex->cmd2_args[0] || pipex->cmd2_args[0][0] == '\0')
	{
		free_pipex(pipex);
		free_env_path(pipex->env_path);
		exit(0);
	}
	if (!pipex->cmd2_path)
		handle_second_child_exit(pipex, pipex->cmd2_args[0]);
	execve(pipex->cmd2_path, pipex->cmd2_args, envp);
	perror("execve");
	handle_second_child_exit(pipex, NULL);
}

