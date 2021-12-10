/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:56:29 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/10 10:37:14 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cat_env(t_shell *minishell, int start_index)
{
	while (minishell->env[start_index + 1])
	{
		minishell->env[start_index] = minishell->env[start_index + 1];
		start_index++;
	}
		minishell->env[start_index] = NULL;
}

int	msh_unset(t_shell *minishell, t_cmd *cmd)
{
	int	i;
	int	var_index;

	i = 1;
	while (cmd->argv[i])
	{
		var_index = search_env(minishell, cmd->argv[i]);
		if (var_index >= 0)
		{
			free(minishell->env[var_index]);
			cat_env(minishell, var_index);
		}
		i++;
	}
	cmd->return_value = 0;
	return (cmd->return_value);
}
