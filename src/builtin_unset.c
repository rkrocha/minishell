/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:56:29 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/06 12:21:09 by rkochhan         ###   ########.fr       */
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

int	msh_unset(t_shell *minishell, t_cmd *cmd) // deve aceitar vários args
{
	int	var_index;

	(void)cmd; // arrumar depois de termos o parsing
	var_index = search_env(minishell, "MAIL"); // tirar var hardcoded
	if (var_index >= 0)
	{
		free(minishell->env[var_index]);
		cat_env(minishell, var_index);
	}
	return (0); // pode retornar >0 caso não consiga unsettar uma ou mais vars
}
