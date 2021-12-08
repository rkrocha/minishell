/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:18:10 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/08 18:49:05 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *cmd)
{
	int	i;
	char	*name;

	i = 0;
	while(cmd[i] != '=')
		i++;
	name = ft_substr(cmd, 0, i);
	return (name);
}

int	msh_export(t_shell *minishell, t_cmd *cmd) // pode aceitar vários args
{
	int	var_actual;
	int	var_pos;
	int	var_last;
	char	*var_name;

	var_name = get_var_name(cmd->cmd_v[1]);  // quebra a string cmd_v
	var_last = env_len(minishell);
	var_pos = search_env(minishell, var_name);
	var_actual = var_last;
	if (var_pos > -1)
		var_actual = var_pos;
	if (var_actual >= ENV_SIZE) /// imprimir erro?
		return (-1);
	if (var_actual == var_pos)
		free(minishell->env[var_actual]);
	free (var_name);
	minishell->env[var_actual] = ft_strdup(cmd->cmd_v[1]);
	return (0); // retonar >0 caso uma var não possa ser exportada
}
