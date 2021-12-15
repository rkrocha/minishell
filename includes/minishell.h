/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:53:48 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/15 13:32:43 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define ENV_SIZE	256

# define TYPE_EXECVE		0
# define TYPE_MINI_CD		1
# define TYPE_MINI_ECHO		2
# define TYPE_MINI_ENV		3
# define TYPE_MINI_EXIT		4
# define TYPE_MINI_EXPORT	5
# define TYPE_MINI_PWD		6
# define TYPE_MINI_UNSET	7

# define PIPE_SEP	29
# define CMD_SEP	31

/*
** type: the type of this cmd (bash builtin, minishell env, minishell cd...)
** argv: command vector, as in ["echo", "-n", "hello", NULL]
** return_value: the value returned from this command after execution
*/
typedef struct s_cmd
{
	t_uchar	type;
	int		return_value; // vai precisar?
	int		argc;
	char	**argv;
	char	*input; // 0 não tem, 1 do arquivo, 2 here doc
	char	**input_file; // se for do tipo 1, tem file
	char	*output; // 0 se não tiver, 1 overwrite, 2 append
	char	**output_file; // se for 1 ou 2, tem file
}	t_cmd;

/*
** env: minishell environment variables
** cdmv: command vector, it is the input from readline separated by pipes(?)
** prompt: minishell prompt, styled and colored
** last_return: return value of the last executed command
*/
typedef struct s_shell
{
	int		data_fd[2];
	int		ret_fd[2];
	t_bool	end;
	char	**env;
	t_list	*cmd_list;
	char	*prompt;
	int		last_return;
	char	*pwd;
	char	*home;
}	t_shell;

void	init_env(t_shell *minishell, const char **envp);
int		search_env(t_shell *minishell, const char *var);
int		env_len(t_shell *minishell);
char	*get_env(t_shell *minishell, const char *var);

int		msh_echo(t_shell *minishell, t_cmd *cmd);
int		msh_env(t_shell *minishell, t_cmd *cmd);
int		msh_exit(t_shell *minishell, t_cmd *cmd);
int		msh_export(t_shell *minishell, t_cmd *cmd);
int		msh_unset(t_shell *minishell, t_cmd *cmd);
int		msh_cd(t_shell *minishell, t_cmd *cmd);
int		msh_pwd(t_shell *minishell, t_cmd *cmd);
int		msh_execve(t_shell *minishell, t_cmd *cmd);

void	cmd_parser(t_shell *minishell, char *cmd);
void	cmd_router(t_shell *minishell);
void	cmd_var_parser(t_shell *minishell, t_cmd *cmd);
void	cmd_home_expand(t_shell *minishell, t_cmd *cmd);
void	cmd_redirects_parser(t_shell *minishell, t_cmd *cmd);
void	cmd_quotes_parser(t_cmd *cmd);

int		is_inquotes(char *str, char *expansion);
t_bool	cmd_error_parser(const char *cmd_line);

char	*single_cmd_parser(t_shell *minishell, char	*str);

void	del_cmd(void *elem);
t_cmd	*get_cmd(void *elem);

char	*ft_strjoin_free(char **s1, char const *s2);

#endif
