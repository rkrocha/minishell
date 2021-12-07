/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:20:40 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/06 11:1411 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_var_name(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

static t_bool	is_inquotes(char *str, char *expansion)
{
	int		quote;
	int		d_quote;
	int		i;

	quote = -1;
	d_quote = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && quote == -1)
			quote = i;
		else if (str[i] == '\'' && quote > -1)
			quote = -1;
		if (str[i] == '\"' && d_quote == -1)
			d_quote = i;
		else if ((str[i] == '\"' && d_quote > -1))
			d_quote = -1;
		if (str + i == expansion && quote > -1			// se está verificando o indice do '$' e existe uma áspa simples aberta
			&& (!(d_quote > -1 && quote > d_quote)))	// not: se existir uma aspa dupla aberta e estiver antes da simples
			return (TRUE);
	}
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
	expansion = malloc(3 * sizeof(char *));
	expansion[2] = NULL;
	expansion[1] = ft_substr(str, 0, i);				 // grava o nome da variável ex: $HOME
	if (i == 1)
		expansion[0] = ft_substr(str, 0, i);
	else
		expansion[0] = get_env(minishell, expansion[1] + 1); // retorna o conteúdo da variável ex: /home/admin
	return (expansion);
}

char	*copy_middle(char **str, char *tracker, int size)
{
	char	*temp;

	temp = ft_substr(tracker, 0, size);
	*str = ft_strjoin_free(str, temp);
	free (temp);
	return (*str);
}

char	*single_cmd_parser(t_shell *minishell, char	*str)
{
	char	*new_str;
	char	*expansion;
	char	*tracker;
	char	**content;

	if (!ft_strchr(str, '$'))
		return (NULL);
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
		new_str = ft_strjoin_free(&new_str, content[(int)is_inquotes(str, expansion)]);
		expansion += ft_strlen(content[1]);
		ft_split_free(&content);
	}
	return (new_str);
}
