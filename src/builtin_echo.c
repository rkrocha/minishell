/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:26:38 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/09 10:32:13 by dpiza            ###   ########.fr       */
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
	if (cmd->argv[1] && !ft_strncmp(cmd->argv[1], "-n", 3))
	{
		print_newline = FALSE;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr(cmd->argv[i]);
		if (cmd->argv[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (print_newline)
		ft_putchar('\n');
	return (0);
}
