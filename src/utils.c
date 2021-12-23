/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:29:06 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/23 13:39:56 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_shell *minishell, int return_value)
{
	rl_clear_history();
	ft_split_free(&minishell->env);
	ft_lstclear(&minishell->cmd_list, del_cmd);
	free(minishell->home);
	free(minishell->pwd);
	free(minishell->prompt);
	exit(return_value);
}

void	del_cmd(void *elem)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)elem;
	ft_split_free(&cmd->argv);
	ft_lstclear(&cmd->input, free);
	ft_lstclear(&cmd->output, free);
	free(cmd);
}
