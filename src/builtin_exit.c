/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:30:17 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/09 21:03:10 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	numeric_argument(char *cmd)
{
	int				i;
	unsigned char	arg;

	i = 0;
	arg = (unsigned char)ft_atoi(cmd);
	if (ft_atoi(cmd) == 0)
	{
		while (cmd[i] && ft_isdigit(cmd[i]))
			i++;
		if (cmd[i] != '\0')
			return (-1);
	}
	return (arg);
}

int	msh_exit(t_shell *minishell, t_cmd *cmd)
{
	if (cmd->argc > 2)
	{
		ft_putendl("minishell: exit: too many arguments");
		cmd->return_value = 1;
		return (cmd->return_value);
	}
	if (cmd->argv[1])
		cmd->return_value = numeric_argument(cmd->argv[1]);
	else
		cmd->return_value = minishell->last_return;
	if (cmd->return_value == -1)
	{
		ft_putstr("minishell: exit: ");
		ft_putstr(cmd->argv[1]);
		ft_putendl(": numeric argument required");
		cmd->return_value = 2;
	}
	minishell->end = TRUE;
	return (cmd->return_value);
}
