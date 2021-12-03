/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:18:10 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/03 15:00:36 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_export(t_shell *minishell, t_cmd *cmd) // pode aceitar vários args
{
	int	var_actual;
	int	var_pos;
	int	var_last;

	(void)cmd;
	var_last = env_len(minishell);
	var_pos = search_env(minishell, "MAIL"); // quebrar a string cdm_v
	var_actual = var_last;
	if (var_pos > -1)
		var_actual = var_pos;
	if (var_actual >= ENV_SIZE)
		return (-1);
	if (var_actual == var_pos)
		free(minishell->env[var_actual]);
	minishell->env[var_actual] = ft_strdup("MAIL=1234");
	return (0); // retonar >0 caso uma var não possa ser exportada
}
