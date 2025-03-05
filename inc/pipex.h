/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:55:55 by acaes             #+#    #+#             */
/*   Updated: 2025/03/05 14:55:55 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// -------------------- Pars --------------------- //
// _____check_args.c_____ //
int		check_args(int ac);
int		check_infile(char *infile);
// _____check_cmds.c_____ //
char	*find_cmd_path(char *cmd, char **env_path);
char	**get_env_path(char **envp);

// -------------------- Pipe -------------------- //
// _____init_pipe.c_____ //
void	init_pipex(t_pipex *pipex, char **envp);
void	free_pipex(t_pipex *pipex);
void	free_env_path(char **env_path);

// -------------------- Exec -------------------- //
// _____child_process.c_____ //
void	first_child(t_pipex *pipex, char **envp);
void	second_child(t_pipex *pipex, char **envp);
// _____init_command.c_____ //
int		init_command(t_pipex *pipex, char **av);
// _____exec_command.c_____ //
int		exec_command(t_pipex *pipex, char **envp);
// _____my_exec.c_____ //
int		my_exec(t_pipex *pipex, char **av, char **envp);

// -------------------- Utils -------------------- //
void	msg_error(char *msg);
void	free_tab(char **tab);
int		p_error(char *msg);

#endif
