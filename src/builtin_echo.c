/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:26:38 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/08 14:24:49 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_echo(t_shell *minishell, t_cmd *cmd)
{
	t_bool	print_newline;
	int		i;

	(void)minishell;
	i = 1;
	print_newline = TRUE;
	if (cmd->cmd_v[1] && !ft_strncmp(cmd->cmd_v[1], "-n", 3))
	{
		print_newline = FALSE;
		i++;
	}
	while (cmd->cmd_v[i])
	{
		ft_putstr(cmd->cmd_v[i]);
		if (cmd->cmd_v[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (print_newline)
		ft_putchar('\n');
	return (0);
}
