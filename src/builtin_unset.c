/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:56:29 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/03 14:01:044 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_unset(t_shell *minishell, t_cmd *cmd) // deve aceitar vários args
{
	int			var_count;
	int			var_index;

	(void)cmd; // arrumar depois de termos o parsing
	var_index = search_env(minishell, "MAIL"); // tirar var hardcoded
	if (var_index >= 0)
	{
		free(minishell->env[var_index]);
		var_count = env_len(minishell);
		minishell->env[var_index] = minishell->env[var_count];
		minishell->env[var_count] = NULL;
	}
	return (0); // pode retornar >0 caso não consiga unsettar uma ou mais vars
}
