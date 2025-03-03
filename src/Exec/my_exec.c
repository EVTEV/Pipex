#include "../../inc/pipex.h"

void	first_child(t_pipex *pipex, char **envp)
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
		free_env_path(pipex->env_paths);
		exit(0);
	}
	execve(pipex->cmd1_path, pipex->cmd1_args, envp);
	perror("execve");
	free_pipex(pipex);
	free_env_path(pipex->env_path);
	exit(127);
}

void	second_child(t_pipex *pipex, char **envp)
{
	int	null_fd;

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
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (!pipex->cmd2_args[0] || pipex->cmd2_args[0][0] == '\0')
	{
		free_pipex(pipex);
		free_env_path(pipex->env_paths);
		exit(0);
	}
	if (!pipex->cmd2_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(pipex->cmd2_args[0], 2);
		ft_putstr_fd("\n", 2);
		free_pipex(pipex);
		free_env_path(pipex->env_paths);
		exit(127);
	}
	execve(pipex->cmd2_path, pipex->cmd2_args, envp);
	perror("execve");
	free_pipex(pipex);
	free_env_path(pipex->env_paths);
	exit(127);
}

int	init_command(t_pipex *pipex, char **av)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->cmd1_args = NULL;
	pipex->cmd2_args = NULL;
	pipex->cmd1_path = NULL;
	pipex->cmd2_path = NULL;
	pipex->outfile_permission_error = 0;
	if (!av[1] || !av[2] || !av[3] || !av[4])
		return (p_error("Error: Missing arguments"));
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile < 0)
		perror(av[1]);
	pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		perror(av[4]);
		if (access(av[4], F_OK) == 0)
			pipex->outfile_permission_error = 1;
	}
	if (av[2][0] == '\0')
		pipex->cmd1_args = ft_split("", ' ');
	else
		pipex->cmd1_args = ft_split(av[2], ' ');
	if (av[3][0] == '\0')
		pipex->cmd2_args = ft_split("", ' ');
	else
		pipex->cmd2_args = ft_split(av[3], ' ');
	if (!pipex->cmd1_args || !pipex->cmd2_args)
		return (1);
	if (pipex->cmd1_args[0] && pipex->cmd1_args[0][0] != '\0')
		pipex->cmd1_path = find_cmd_path(pipex->cmd1_args[0], pipex->env_paths);
	else
		pipex->cmd1_path = NULL;
	if (pipex->cmd2_args[0] && pipex->cmd2_args[0][0] != '\0')
		pipex->cmd2_path = find_cmd_path(pipex->cmd2_args[0], pipex->env_paths);
	else
		pipex->cmd2_path = NULL;
	return (0);
}

int	execute_command(t_pipex *pipex, char **envp)
{
	int	status1;
	int	status2;
	int	exit_status;

	if (pipe(pipex->pipe_fd) < 0)
		return (p_error("Pipe error"));
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

int	my_exec(t_pipex *pipex, char **av, char **envp)
{
	int	return_value;

	pipex->env_paths = get_env_paths(envp);
	if (init_command(pipex, av) != 0)
	{
		free_env_paths(pipex->env_paths);
		return (1);
	}
	return_value = execute_command(pipex, envp);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	free_pipex(pipex);
	free_env_paths(pipex->env_paths);
	if (pipex->permission)
		return (1);
	return (return_value);
}
