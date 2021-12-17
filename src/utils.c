/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:29:06 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/17 11:37:11 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_cmd(void *elem)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)elem;
	ft_split_free(&cmd->argv);
	ft_lstclear(&cmd->input, free);
	ft_lstclear(&cmd->output, free);
	free(cmd);
}
