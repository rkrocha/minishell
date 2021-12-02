/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:53:06 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/02 15:28:55 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_router(t_shell *minishell)
{
	static	void (*const func_ptr[8])(t_shell *, t_cmd *) = {
		NULL, NULL, NULL, msh_env, msh_exit, NULL, NULL, NULL};
	t_list	*tracker;
	t_cmd	*current;

	tracker = minishell->cmd_list;
	while (tracker)
	{
		current = ((t_cmd *)tracker->content);
		func_ptr[current->type](minishell, current);
		tracker = tracker->next;
	}
}
