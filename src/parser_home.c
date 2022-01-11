/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 09:21:58 by rkochhan          #+#    #+#             */
/*   Updated: 2022/01/11 10:55:34 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_home(t_shell *minishell, char **cmd)
{
	char	*home;
	char	*append;
	char	*full_path;

	if (search_env(minishell, "HOME") >= 0)
		home = get_env(minishell, "HOME");
	else
		home = ft_strdup(minishell->home);
	append = ft_substr(*cmd, 1, ft_strlen(*cmd));
	free(*cmd);
	full_path = ft_strjoin_free(&home, append);
	free(append);
	*cmd = full_path;
}

char	*export_home_expand(t_shell *minishell, char *var)
{
	char	**var_strs;
	char	*var_expanded;
	char	*sep;
	char	*exp;

	sep = ft_strchr(var, '=');
	if (sep)
		exp = ft_strchr(sep, '~');
	if (!sep || !exp || exp != sep + 1)
		return (ft_strdup(var));
	if (*(exp + 1) == '\0' || *(exp + 1) == '/')
	{
		var_strs = ft_split(var, '=');
		expand_home(minishell, &var_strs[1]);
		var_expanded = ft_strjoin(var_strs[0], "=");
		var_expanded = ft_strjoin_free(&var_expanded, var_strs[1]);
		ft_split_free(&var_strs);
		return (var_expanded);
	}
	else
		return (ft_strdup(var));
}

void	cmd_home_expand(t_shell *minishell, t_cmd *cmd)
{
	int		i;
	char	**argv;

	i = 0;
	argv = cmd->argv;
	while (argv[i])
	{
		if (argv[i][0] == '~' && (!argv[i][1] || argv[i][1] == '/'))
			expand_home(minishell, &argv[i]);
		i++;
	}
}
