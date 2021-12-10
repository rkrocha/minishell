/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:53:06 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/10 14:28:01 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int msh_dummy(t_shell *minishell, t_cmd *cmd) // remover
// {
// 	(void)minishell;
// 	(void)cmd;
// 	return (0);
// }

void	cmd_router(t_shell *minishell)
{
	static int (*const	func_ptr[8])(t_shell *, t_cmd *) = {
		msh_execve, msh_cd, msh_echo, msh_env,
		msh_exit, msh_export, msh_pwd, msh_unset};
	t_list				*tracker;
	t_cmd				*current;

	tracker = minishell->cmd_list;
	while (tracker)
	{
		current = ((t_cmd *)tracker->content);
		minishell->last_return = func_ptr[current->type](minishell, current);
		// atualizar var ? de ambiente
		tracker = tracker->next;
	}
}
