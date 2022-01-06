/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 10:53:49 by rkochhan          #+#    #+#             */
/*   Updated: 2022/01/06 13:40:25 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_valid_end(char *name, char *needle)
{
	int		needle_len;
	int		name_len;

	needle_len = ft_strlen(needle);
	name_len = ft_strlen(name);
	if (needle_len > name_len)
		return (FALSE);
	if (ft_strncmp(&name[name_len - needle_len], needle, needle_len) == 0)
		return (TRUE);
	return (FALSE);
}

static char	**get_expansions(t_shell *msh, char *expansion)
{
	struct dirent	*ret;
	DIR				*folder;
	char			*expansion_str;
	char			**expansion_args;

	folder = opendir(msh->pwd);
	expansion_str = NULL;
	if (!folder)
		return (NULL);
	ret = readdir(folder);
	while (ret)
	{
		if (is_valid_expansion(ret->d_name, expansion))
			wildcard_expand(&expansion_str, ret->d_name, expansion);
		ret = readdir(folder);
	}
	if (!expansion_str)
		expansion_str = ft_strdup(expansion);
	expansion_args = ft_split(expansion_str, '\30');
	free(expansion_str);
	closedir(folder);
	while (matrix_sort(expansion_args) != TRUE)
		;
	return (expansion_args);
}

static int	arg_wildcard_parser(t_shell *msh, t_cmd *cmd, int current_arg)
{
	char	**new_argv;
	char	**expansion_args;
	int		expansion_len;

	expansion_args = get_expansions(msh, cmd->argv[current_arg]);
	expansion_len = matrix_len(expansion_args);
	new_argv = (char **)ft_calloc(expansion_len + matrix_len(cmd->argv) + 1,
			sizeof(char *));
	ft_memcpy(new_argv, cmd->argv, current_arg * sizeof(char *));
	ft_memcpy(&new_argv[matrix_len(new_argv)], expansion_args,
		expansion_len * sizeof(char *));
	ft_memcpy(&new_argv[matrix_len(new_argv)], &cmd->argv[current_arg + 1],
		matrix_len(&cmd->argv[current_arg + 1]) * sizeof(char *));
	free(cmd->argv[current_arg]);
	free(cmd->argv);
	free(expansion_args);
	cmd->argv = new_argv;
	return (matrix_len(new_argv));
}

void	cmd_wildcard_parser(t_shell *msh, t_cmd *new_cmd)
{
	int		i;
	char	*asterisk;

	i = 0;
	while (new_cmd->argv[i])
	{
		asterisk = ft_strchr(new_cmd->argv[i], '*');
		if (asterisk && !is_inquotes(new_cmd->argv[i], asterisk))
			i += arg_wildcard_parser(msh, new_cmd, i);
		else
			i++;
	}
	new_cmd->argc = matrix_len(new_cmd->argv);
}