/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:36:10 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/06 10:24:15 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	define_type(t_cmd *new_cmd)
{
	if (!ft_strncmp(new_cmd->cmd_v[0], "cd", 3))
		new_cmd->type = TYPE_MINI_CD;
	else if (!ft_strncmp(new_cmd->cmd_v[0], "echo", 5))
		new_cmd->type = TYPE_MINI_ECHO;
	else if (!ft_strncmp(new_cmd->cmd_v[0], "env", 4))
		new_cmd->type = TYPE_MINI_ENV;
	else if (!ft_strncmp(new_cmd->cmd_v[0], "exit", 5))
		new_cmd->type = TYPE_MINI_EXIT;
	else if (!ft_strncmp(new_cmd->cmd_v[0], "export", 7))
		new_cmd->type = TYPE_MINI_EXPORT;
	else if (!ft_strncmp(new_cmd->cmd_v[0], "pwd", 4))
		new_cmd->type = TYPE_MINI_PWD;
	else if (!ft_strncmp(new_cmd->cmd_v[0], "unset", 6))
		new_cmd->type = TYPE_MINI_UNSET;
	else
		new_cmd->type = TYPE_EXECVE;
}

static void	cmd_space_parser(char *cmd_line)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while(cmd_line[i])
	{
		if (quote == '\0' && (cmd_line[i] == '\'' || cmd_line[i] == '\"'))
			quote = cmd_line[i];
		else if (quote != '\0' && cmd_line[i] == quote)
			quote = '\0';
		if (quote == '\0' && ft_isspace(cmd_line[i]))
			cmd_line[i] = CMD_SEP;
		i++;
	}
}

static void	cmd_pipe_parser(char *cmd_line)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while(cmd_line[i])
	{
		if (quote == '\0' && (cmd_line[i] == '\'' || cmd_line[i] == '\"'))
			quote = cmd_line[i];
		else if (quote != '\0' && cmd_line[i] == quote)
			quote = '\0';
		if (quote == '\0' && cmd_line[i] == '|')
			cmd_line[i] = PIPE_SEP;
		i++;
	}
}

void	cmd_parser(t_shell *minishell, char *cmd_line)
{
	char	**cmds_split_by_pipe;
	t_cmd	*new_cmd;
	int		i;

	cmd_pipe_parser(cmd_line);
	cmd_space_parser(cmd_line);
	cmds_split_by_pipe = ft_split(cmd_line, PIPE_SEP);
	i = 0;
	while (cmds_split_by_pipe[i])
	{
		new_cmd = malloc(sizeof(t_cmd));
		ft_bzero(new_cmd, sizeof(t_cmd));
		new_cmd->cmd_v = ft_split(cmds_split_by_pipe[i], CMD_SEP);
		cmd_var_parser(minishell, new_cmd);
		define_type(new_cmd);
		ft_lstadd_back(&minishell->cmd_list, ft_lstnew(new_cmd));
		i++;
	}
	ft_split_free(&cmds_split_by_pipe);
}
