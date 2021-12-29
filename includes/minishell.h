/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:53:48 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/29 14:26:59 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>

# define ENV_SIZE	256

# define TYPE_EXECVE		0
# define TYPE_MINI_CD		1
# define TYPE_MINI_ECHO		2
# define TYPE_MINI_ENV		3
# define TYPE_MINI_EXIT		4
# define TYPE_MINI_EXPORT	5
# define TYPE_MINI_PWD		6
# define TYPE_MINI_UNSET	7
# define TYPE_DUMMY			8

# define PIPE_SEP	29
# define CMD_SEP	31

/*
** type: the type of this cmd (bash builtin, minishell env, minishell cd...)
** argc: command arg count
** argv: command vector, as in ["echo", "-n", "hello", NULL]
** input: list of parsed input redirects
** output: list of parsed output redirects
** return_value: the value returned from this command after execution
*/
typedef struct s_cmd
{
	t_uchar	type;
	int		argc;
	char	**argv;
	t_list	*input;
	t_list	*output;
	int		return_value;
}	t_cmd;

/*
** env: minishell environment variables
** pwd: current working directory
** prompt: minishell prompt, styled and colored
** home: home path acquired from shell env on minishell init
** cmd_list: list of parsed commands in the form of t_cmd struct
** data_fd: pipe fds for data transfer between commands
** ret_fd: pipe fds for return values between parent and children processes
** last_return: return value of the last executed command
** end: terminating condition for minishell
*/
typedef struct s_shell
{
	char	**env;
	char	*pwd;
	char	*prompt;
	char	*home;
	t_list	*cmd_list;
	int		data_fd[2];
	int		ret_fd[2];
	int		last_return;
	t_bool	end;
}	t_shell;

/*
** env_manager.c:
*/
void	init_env(t_shell *minishell, const char **envp);
int		search_env(t_shell *minishell, const char *var);
int		env_len(t_shell *minishell);
char	*get_env(t_shell *minishell, const char *var);
t_bool	sort_env(t_shell *msh);

/*
** builtin_*.c:
*/
int		msh_cd(t_shell *minishell, t_cmd *cmd);
int		msh_echo(t_shell *minishell, t_cmd *cmd);
int		msh_env(t_shell *minishell, t_cmd *cmd);
int		msh_exit(t_shell *minishell, t_cmd *cmd);
int		msh_export(t_shell *minishell, t_cmd *cmd);
int		msh_pwd(t_shell *minishell, t_cmd *cmd);
int		msh_unset(t_shell *minishell, t_cmd *cmd);
int		msh_dummy(t_shell *minishell, t_cmd *cmd);

/*
** execve.c:
*/
int		msh_execve(t_shell *minishell, t_cmd *cmd);

/*
** parser*.c:
*/
void	cmd_parser(t_shell *minishell, char *cmd);
void	cmd_home_expand(t_shell *minishell, t_cmd *cmd);
void	cmd_redirects_parser(t_cmd *cmd);
void	cmd_quotes_parser(t_cmd *cmd);
void	arg_quotes_parser(char *arg);
t_bool	cmd_error_parser(const char *cmd_line);
char	*divide_redirects(char *cmd_line);
char	*single_cmd_parser(t_shell *minishell, char	*str);
int		is_inquotes(char *str, char *expansion);

/*
** router*.c:
*/
void	cmd_router(t_shell *minishell);
void	cmd_exec_pipes_iter(t_shell *msh, t_list *tracker);

/*
** redirect*.c:
*/
void	redirect(t_shell *msh, t_cmd *cmd, int *redir);
int		here_doc(t_shell *msh, char *delim);

/*
** utils.c:
*/
void	del_cmd(void *elem);
void	free_and_exit(t_shell *minishell, int return_value);
int		throw_err(char *cmd, int err_n);
void	sigint(int signum);
int		ft_strccmp(const char *s1, const char *s2, char c);

char	*ft_strjoin_free(char **s1, char const *s2);

/*
** fd_utils.c:
*/
t_bool	check_input(void);
void	print_from_pipe(int fd);

#endif
