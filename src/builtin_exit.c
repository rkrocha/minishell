/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:30:17 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/03 15:01:11 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exit(t_shell *minishell, t_cmd *cmd)
{
	(void)cmd;
	minishell->end = TRUE;
	return (0); // futuramente tem que ser cmd->cmd_v[1], se existir;
}
