/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:30:17 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/08 22:37:08 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	numeric_argument(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && ft_isdigit(cmd[i]))
		i++;
	if (cmd[i] != '\0')
		return (-1);
	return (ft_atoi(cmd) % 256);
}

int	msh_exit(t_shell *minishell, t_cmd *cmd)
{
	if (cmd->cmd_v[1])
		cmd->return_value = numeric_argument(cmd->cmd_v[1]);
	else
		cmd->return_value = 0;
	if (cmd->return_value == -1)
	{
		ft_putstr("minishell: exit: ");
		ft_putstr(cmd->cmd_v[1]);
		ft_putstr(": ");
		ft_putendl("numeric argument required");
		cmd->return_value = 2;
	}
	minishell->end = TRUE;
	return (cmd->return_value);
}
