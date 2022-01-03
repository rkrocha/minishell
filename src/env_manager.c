/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:55:10 by rkochhan          #+#    #+#             */
/*   Updated: 2022/01/03 11:50:31 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_shell *minishell, const char *var)
{
	int		i;
	char	*var_join;
	char	*var_content;

	var_join = ft_strjoin(var, "=");
	i = -1;
	while (minishell->env[++i])
	{
		if (!ft_strncmp(minishell->env[i], var_join, ft_strlen(var_join)))
		{
			var_content = ft_substr(minishell->env[i], ft_strlen(var_join),
					ft_strlen(minishell->env[i]) - ft_strlen(var_join));
			free(var_join);
			return (var_content);
		}
	}
	free(var_join);
	return (ft_strdup(""));
}

int	env_len(t_shell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
		i++;
	return (i);
}

int	search_env(t_shell *minishell, const char *var)
{
	int		i;
	char	*var_join;

	var_join = ft_strjoin(var, "=");
	i = -1;
	while (minishell->env[++i])
	{
		if (!ft_strncmp(minishell->env[i], var_join, ft_strlen(var_join)))
		{
			free(var_join);
			return (i);
		}
	}
	free(var_join);
	return (-1);
}

t_bool	sort_env(t_shell *msh)
{
	int		i;
	t_bool	end_of_sort;

	i = 0;
	end_of_sort = TRUE;
	while (msh->env[i])
	{
		if (msh->env[i + 1]
			&& ft_strccmp(msh->env[i], msh->env[i + 1], '=') > 0)
		{
			end_of_sort = FALSE;
			ft_strswap(&msh->env[i], &msh->env[i + 1]);
		}
		i++;
	}
	return (end_of_sort);
}

void	init_env(t_shell *minishell, const char **envp)
{
	int	i;
	int	j;

	minishell->env = (char **)ft_calloc(BASE_ENV_SIZE, sizeof(char *));
	minishell->env_size = BASE_ENV_SIZE;
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!ft_strnstr(envp[i], "_WORKSPACE_",
				ft_strchr(envp[i], '=') - &envp[i][0]))
		{
			if (j == minishell->env_size - 1)
				env_realloc(minishell);
			minishell->env[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	while (sort_env(minishell) != TRUE)
		;
	minishell->home = get_env(minishell, "HOME");
	minishell->pwd = get_env(minishell, "PWD");
}
