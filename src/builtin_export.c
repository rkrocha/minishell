/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:18:10 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/09 15:26:09 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *cmd)
{
	int		i;
	char	*name;

	i = 0;
	while (cmd[i] != '=')
		i++;
	name = ft_substr(cmd, 0, i);
	return (name);
}

static int	save_var(t_shell *minishell, char *content)
{
	char	*var_name;
	int		var_index;

	if (!ft_isalpha(content[0]))
	{
		printf("minishell: export: `%s`: not a valid identifier\n", content); /// usar perror?
		return (1);
	}
	if (!ft_strchr(content, '='))
		return (0);
	var_name = get_var_name(content);
	var_index = search_env(minishell, var_name);
	free(var_name);
	if (var_index == -1)
		var_index = env_len(minishell);
	if (var_index >= ENV_SIZE - 1)
	{
		printf("minishell: export: full environment\n");
		return (1);
	}
	free(minishell->env[var_index]);
	minishell->env[var_index] = ft_strdup(content);
	return (0);
}

int	msh_export(t_shell *minishell, t_cmd *cmd)
{
	int	i;
	int	fail_count;

	i = 1;
	fail_count = 0;
	while (cmd->argv[i])
	{
		fail_count += save_var(minishell, cmd->argv[i]);
		i++;
	}
	if (fail_count)
		fail_count = 1;
	cmd->return_value = fail_count;
	return (fail_count);
}
