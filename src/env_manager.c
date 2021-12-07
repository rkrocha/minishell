/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:55:10 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/07 11:02:09 by dpiza            ###   ########.fr       */
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
	while(minishell->env[++i])
	{
		if (ft_strncmp(minishell->env[i], var, ft_strlen(var)) == 0)
		{
			var_content = ft_substr(minishell->env[i], ft_strlen(var_join),
				ft_strlen(minishell->env[i]) - ft_strlen(var_join));
			free(var_join);
			return (var_content);
		}
	}
	free(var_join);
	return (NULL);
}

int		env_len(t_shell *minishell)
{
	int	i;

	i = 0;
	while(minishell->env[i])
		i++;
	return (i);
}

int		search_env(t_shell *minishell, const char *var)
{
	int		i;
	char	*var_join;

	var_join = ft_strjoin(var, "=");
	i = -1;
	while(minishell->env[++i])
	{
		if (ft_strncmp(minishell->env[i], var, ft_strlen(var)) == 0)
		{
			free(var_join);
			return (i);
		}
	}
	free(var_join);
	return (-1);
}

void	init_env(t_shell *minishell, const char **envp)
{
	int	i;

	minishell->env = (char **)ft_calloc(ENV_SIZE, sizeof(char *));
	i = -1;
	while (envp[++i])
		minishell->env[i] = ft_strdup(envp[i]);
}
