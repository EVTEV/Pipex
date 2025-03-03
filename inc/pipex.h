#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/inc/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**env_path;
	char	**cmd1_args;
	char	**cmd2_args;
	char	*cmd1_path;
	char	*cmd2_path;
	int		permission;
}	t_pipex;

// ---------- Pars ---------- //
// _____check_args.c_____ //
int		check_args(int ac);
int		check_infile(char *infile);
// _____check_cmds.c_____ //
char	*find_cmd_path(char *cmd, char **env_path);
char	**get_env_path(char **envp);

// ---------- Exec ---------- //
// _____init_pipe.c_____ //
void	init_pipex(t_pipex *pipex, char **envp);
void	free_pipex(t_pipex *pipex);
void	free_env_path(char **env_path);

// _____my_exec.c_____ //
void	first_child(t_pipex *pipex, char **envp);
void	second_child(t_pipex *pipex, char **envp);
int		init_command(t_pipex *pipex, char **av);
int		execute_command(t_pipex *pipex, char **envp);
int		my_exec(t_pipex *pipex, char **av, char **envp);

// ---------- Utils ---------- //
void	msg_error(char *msg);
void	free_tab(char **tab);
int		p_error(char *msg);

#endif
