/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:20:40 by rkochhan          #+#    #+#             */
/*   Updated: 2022/01/07 14:14:45 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_var_name(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

static char	**var_expand(t_shell *minishell, char *str)
{
	int		i;
	char	**expansion;

	i = 0;
	while (str[++i])
	{
		if (!is_var_name(str[i]))
			break ;
	}
	if (i == 1 && str[i] == '?')
		i++;
	expansion = malloc(3 * sizeof(char *));
	expansion[2] = NULL;
	expansion[1] = ft_substr(str, 0, i);
	if (i == 2 && !ft_strncmp(expansion[1], "$?", 2))
		expansion[0] = ft_itoa(minishell->last_return);
	else if (i == 1)
		expansion[0] = ft_substr(str, 0, i);
	else
		expansion[0] = get_env(minishell, expansion[1] + 1);
	return (expansion);
}

char	*copy_middle(char **str, char *tracker, int size)
{
	char	*temp;

	temp = ft_substr(tracker, 0, size);
	*str = ft_strjoin_free(str, temp);
	free(temp);
	return (*str);
}

char	*single_arg_parser(t_shell *minishell, char	*str)
{
	char	*new_str;
	char	*expansion;
	char	*tracker;
	char	**content;

	new_str = ft_strdup("");
	expansion = str;
	while (expansion)
	{
		tracker = expansion;
		expansion = ft_strchr(expansion, '$');
		if (!expansion)
		{
			new_str = ft_strjoin_free(&new_str, tracker);
			break ;
		}
		if (expansion != tracker)
			new_str = copy_middle(&new_str, tracker, expansion - tracker);
		content = var_expand(minishell, expansion);
		new_str = ft_strjoin_free(&new_str,
				content[is_inquotes(str, expansion) == 1]);
		expansion += ft_strlen(content[1]);
		ft_split_free(&content);
	}
	return (new_str);
}
