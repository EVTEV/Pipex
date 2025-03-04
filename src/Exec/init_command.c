#include "../../inc/pipex.h"

static int	setup_file(t_pipex *pipex, char **av)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile < 0)
		perror(av[1]);
	pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		perror(av[4]);
		if (access(av[4], F_OK) == 0)
			pipex->permission = 1;
	}
	return (0);
}

static int	setup_command(t_pipex *pipex, char **av)
{
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
	return (0);
}

static int	find_command_path(t_pipex *pipex)
{
	if (pipex->cmd1_args[0] && pipex->cmd1_args[0][0] != '\0')
		pipex->cmd1_path = find_cmd_path(pipex->cmd1_args[0], pipex->env_path);
	else
		pipex->cmd1_path = NULL;
	if (pipex->cmd2_args[0] && pipex->cmd2_args[0][0] != '\0')
		pipex->cmd2_path = find_cmd_path(pipex->cmd2_args[0], pipex->env_path);
	else
		pipex->cmd2_path = NULL;
	return (0);
}

int	init_command(t_pipex *pipex, char **av)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->cmd1_args = NULL;
	pipex->cmd2_args = NULL;
	pipex->cmd1_path = NULL;
	pipex->cmd2_path = NULL;
	pipex->permission = 0;

	if (!av[1] || !av[2] || !av[3] || !av[4])
		return (p_error("Error: Missing arguments"));
	setup_file(pipex, av);
	if (setup_command(pipex, av) != 0)
		return (1);
	return (find_command_path(pipex));
}
