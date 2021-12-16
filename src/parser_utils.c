/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:04:03 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/16 13:59:25 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	attribute_quotes(int *quote1, int value1, int *quote2, int value2)
{
	*quote1 = value1;
	*quote2 = value2; ////   esses nomes passam na norma?
}

int	is_inquotes(char *str, char *expansion)
{
	int		quote[3];
	int		d_quote[3];
	int		i;

	ft_bzero(quote, sizeof(quote));
	ft_bzero(d_quote, sizeof(d_quote));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && quote[2] == 0 && d_quote[2] == 0)
			attribute_quotes(&quote[0], i + 1, &quote[2], 1);
		else if (str[i] == '\'' && quote[2] > 0)
			attribute_quotes(&quote[1], i + 1, &quote[2], 0);
		if (str[i] == '\"' && d_quote[2] == 0 && quote[2] == 0)
			attribute_quotes(&d_quote[0], i + 1, &d_quote[2], 1);
		else if ((str[i] == '\"' && d_quote[2] > 0))
			attribute_quotes(&d_quote[1], i + 1, &d_quote[2], 0);
		if (str + i == expansion)
			return (quote[2] + d_quote[2] * 10);
	}
	return (-1);
}
