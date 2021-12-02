/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:35:27 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/02 15:35:45 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_env(t_shell *minishell, t_cmd *cmd)
{
	int	i;

	(void)cmd;
	i = 0;
	while (minishell->env[i])
	{
		ft_putendl(minishell->env[i]);
		i++;
	}
	minishell->last_return = 0;
}
