/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:36:10 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/27 14:49:25 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	define_type(t_cmd *new_cmd)
{
	if (!new_cmd->argv[0])
		new_cmd->type = TYPE_DUMMY;
	else if (!ft_strncmp(new_cmd->argv[0], "cd", 3))
		new_cmd->type = TYPE_MINI_CD;
	else if (!ft_strncmp(new_cmd->argv[0], "echo", 5))
		new_cmd->type = TYPE_MINI_ECHO;
	else if (!ft_strncmp(new_cmd->argv[0], "env", 4))
		new_cmd->type = TYPE_MINI_ENV;
	else if (!ft_strncmp(new_cmd->argv[0], "exit", 5))
		new_cmd->type = TYPE_MINI_EXIT;
	else if (!ft_strncmp(new_cmd->argv[0], "export", 7))
		new_cmd->type = TYPE_MINI_EXPORT;
	else if (!ft_strncmp(new_cmd->argv[0], "pwd", 4))
		new_cmd->type = TYPE_MINI_PWD;
	else if (!ft_strncmp(new_cmd->argv[0], "unset", 6))
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
	while (cmd_line[i])
	{
		if (quote == '\0' && (cmd_line[i] == '\'' || cmd_line[i] == '\"'))
			quote = cmd_line[i];
		else if (quote != '\0' && cmd_line[i] == quote)
			quote = '\0';
		if (quote == '\0' && cmd_line[i] != '\n' && ft_isspace(cmd_line[i]))
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
	while (cmd_line[i])
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

void	cmd_var_parser(t_shell *minishell, t_cmd *cmd)
{
	int		i;
	char	*cmd_expanded;

	(void)minishell;
	i = -1;
	while (cmd->argv[++i])
	{
		// printf("ORIGINAL_CMD: %s\n", cmd->argv[i]);
		if (!ft_strchr(cmd->argv[i], '$'))
			continue ;
		cmd_expanded = single_cmd_parser(minishell, cmd->argv[i]);
		free(cmd->argv[i]);
		cmd->argv[i] = cmd_expanded;
		// printf("EXPANDED_CMD: %s\n", cmd->argv[i]);
	}
	cmd->argc = i;
}

void	cmd_parser(t_shell *minishell, char *cmd_line)
{
	char	**cmds_split_by_pipe;
	t_cmd	*new_cmd;
	int		i;

	cmd_pipe_parser(cmd_line);
	cmd_line = divide_redirects(cmd_line);
	cmd_space_parser(cmd_line);
	cmds_split_by_pipe = ft_split(cmd_line, PIPE_SEP);
	free(cmd_line);
	i = 0;
	while (cmds_split_by_pipe[i])
	{
		new_cmd = malloc(sizeof(t_cmd));
		ft_bzero(new_cmd, sizeof(t_cmd));
		new_cmd->argv = ft_split(cmds_split_by_pipe[i], CMD_SEP);
		cmd_var_parser(minishell, new_cmd);
		cmd_home_expand(minishell, new_cmd);
		cmd_redirects_parser(new_cmd);
		cmd_quotes_parser(new_cmd);
		define_type(new_cmd);
		ft_lstadd_back(&minishell->cmd_list, ft_lstnew(new_cmd));
		i++;
	}
	ft_split_free(&cmds_split_by_pipe);
}
