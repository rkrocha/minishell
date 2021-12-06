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

// static t_bool	is_var_name(char c)
// {
// 	if (ft_isalnum(c) || c == '_')
// 		return (TRUE);
// 	return (FALSE);
// }

// static int	var_expand(char *str, int i, char **new_str)
// {
// 	int		j;
// 	char	*expansion_name;

// 	(void)new_str;
// 	i++;
// 	j = 0;
// 	while (str[i + j])
// 	{
// 		if (!is_var_name(str[i + j]))
// 			break ;
// 		j++;
// 	}
// 	expansion_name = ft_substr(str, i, j);
// 	printf("%s\n", expansion_name);
// 	free(expansion_name);
// 	return (j);
// }

// static char	*single_cmd_parser(char *str)
// {
// 	int		i;
// 	char	quote;
// 	char	*new_str;

// 	i = 0;
// 	quote = '\0';
// 	new_str = NULL;
// 	while (str[i])
// 	{
// 		if (quote == '\0' && str[i] == '\'')
// 			quote = str[i];
// 		else if (quote == '\'' && str[i] == '\'')
// 			quote = '\0';
// 		if (quote == '\0' && str[i] == '$')
// 			i += var_expand(str, i, &new_str);
// 		else
// 			i += cat_literal(str, i, &new_str);
// 		i++;
// 	}
// 	return ("abc");
// }

static t_bool	is_inquotes(char *str, char *expansion)
{
	char	*quote_open;
	char	*quote_close;

	quote_open = str;
	while (quote_open)
	{
		quote_open = ft_strchr(quote_open, '\'');
		if (!quote_open)
			return (FALSE);
		quote_close = ft_strchr(++quote_open, '\'');
		if (!quote_close || (quote_open < expansion && quote_close > expansion))
			return (TRUE);
		quote_open = quote_close++;
	}
	return (FALSE);
}

static char	*single_cmd_parser(char	*str)
{
	char	*expansion;
	char	*tracker;
	char	*new_str;

	new_str = NULL;
	if (!ft_strchr(str, '$'));
		return (new_str);
	expansion = str;
	tracker = str;
	while (1)
	{
		expansion = ft_strchr(expansion, '$');


	}
}

void	cmd_var_parser(t_shell *minishell, t_cmd *cmd)
{
	int		i;
	// int		start_index;
	char	*cmd_expanded;

	(void)minishell;
	i = -1;

	while(cmd->cmd_v[++i])
	{
		cmd_expanded = single_cmd_parser(cmd->cmd_v[i]);
		if (!cmd_expanded)
			continue ;
		free(cmd->cmd_v[i]);
		cmd->cmd_v[i] = cmd_expanded;
	}
}
