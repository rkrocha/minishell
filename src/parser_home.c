/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 09:21:58 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/12 13:45:35 by rkochhan         ###   ########.fr       */
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
