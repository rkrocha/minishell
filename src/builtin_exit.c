/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:30:17 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/08 12:58:09 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exit(t_shell *minishell, t_cmd *cmd)
{
	if (cmd->cmd_v[1] && ft_atoi(cmd->cmd_v[1]))
		cmd->return_value = ft_atoi(cmd->cmd_v[1]);
	else
		cmd->return_value = 0;
	minishell->end = TRUE;
	return (cmd->return_value); // futuramente tem que ser cmd->cmd_v[1], se existir; ft_atoi retorna 0 em caso de erro?
}
