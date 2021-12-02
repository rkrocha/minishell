/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:36:10 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/02 15:23:35 by rkochhan         ###   ########.fr       */
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

void	cmd_parser(t_shell *minishell, char *cmd)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	ft_bzero(new_cmd, sizeof(t_cmd));
	new_cmd->cmd_v = ft_split(cmd, ' ');
	define_type(new_cmd);
	ft_lstadd_back(&minishell->cmd_list, ft_lstnew(new_cmd));
}
