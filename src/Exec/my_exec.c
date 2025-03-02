#include "../../inc/pipex.h"

void	first_child(t_pipex *pipex, char **envp)
{
	if (pipex->infile < 0)
		exit(1);
	if (!pipex->cmd1_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(pipex->cmd1_args[0], 2);
		ft_putstr_fd("\n", 2);
		free_pipex(pipex);
		exit(127);
	}
	if (dup2(pipex->infile, STDIN_FILENO) < 0)
		msg_error("dup2 error");
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) < 0)
		msg_error("dup2 error");
	close(pipex->pipe_fd[0]);
	execve(pipex->cmd1_path, pipex->cmd1_args, envp);
	perror("execve error");
	free_pipex(pipex);
	exit(1);
}

void	second_child(t_pipex *pipex, char **envp)
{
	if (pipex->outfile < 0)
		exit(1);
	if (!pipex->cmd2_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(pipex->cmd2_args[0], 2);
		ft_putstr_fd("\n", 2);
		free_pipex(pipex);
		exit(127);
	}
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) < 0)
		msg_error("dup2 error");
	if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
		msg_error("dup2 error");
	close(pipex->pipe_fd[1]);
	execve(pipex->cmd2_path, pipex->cmd2_args, envp);
	perror("execve error");
	free_pipex(pipex);
	exit(1);
}

int	init_command(t_pipex *pipex, char **av)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile < 0)
		perror("Error opening input file");
	pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		perror("Error opening output file");
	pipex->cmd1_args = ft_split(av[2], ' ');
	pipex->cmd2_args = ft_split(av[3], ' ');
	pipex->cmd1_path = find_cmd_path(pipex->cmd1_args[0], pipex->env_paths);
	pipex->cmd2_path = find_cmd_path(pipex->cmd2_args[0], pipex->env_paths);
	return (0);
}

int	execute_command(t_pipex *pipex, char **envp)
{
	int	status;

	if (pipe(pipex->pipe_fd) < 0)
		return (p_error("Pipe error"));
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		return (p_error("Fork error"));
	if (pipex->pid1 == 0)
		first_child(pipex, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		return (p_error("Fork error"));
	if (pipex->pid2 == 0)
		second_child(pipex, envp);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->pid1, &status, 0);
	waitpid(pipex->pid2, &status, 0);
	return (WEXITSTATUS(status));
}

int	my_exec(t_pipex *pipex, char **av, char **envp)
{
	if (init_command(pipex, av) != 0)
		return (1);
	return (execute_command(pipex, envp));
}
