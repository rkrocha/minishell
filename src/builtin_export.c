/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:18:10 by dpiza             #+#    #+#             */
/*   Updated: 2022/01/11 11:00:32 by dpiza            ###   ########.fr       */
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
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(content, 2);
		ft_putendl_fd("`: not a valid identifier", 2);
		return (1);
	}
	if (!ft_strchr(content, '='))
		return (0);
	var_name = get_var_name(content);
	var_index = search_env(minishell, var_name);
	free(var_name);
	if (var_index == -1)
		var_index = env_len(minishell);
	if (var_index == minishell->env_size - 1)
		env_realloc(minishell);
	free(minishell->env[var_index]);
	minishell->env[var_index] = export_home_expand(minishell, content);
	return (0);
}

static void	print_vars(t_shell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(minishell->env[i], 1);
		i++;
	}
}

void	env_realloc(t_shell *msh)
{
	char	**new_env;

	new_env = (char **)ft_calloc(msh->env_size + BASE_ENV_SIZE, sizeof(char *));
	ft_memcpy(new_env, msh->env, msh->env_size * sizeof(char *));
	msh->env_size += BASE_ENV_SIZE;
	free(msh->env);
	msh->env = new_env;
}

int	msh_export(t_shell *minishell, t_cmd *cmd)
{
	int	i;
	int	fail_count;

	i = 1;
	fail_count = 0;
	if (cmd->argc == 1)
		print_vars(minishell);
	while (cmd->argv[i])
	{
		fail_count += save_var(minishell, cmd->argv[i]);
		i++;
	}
	if (fail_count)
		fail_count = 1;
	cmd->return_value = fail_count;
	while (sort_env(minishell) != TRUE)
		;
	return (fail_count);
}
