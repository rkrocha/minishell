/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:55:10 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/06 12:21:11 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
