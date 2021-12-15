/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:04:03 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/15 12:03:29 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	attribute_quotes(int *quote1, int value1, int *quote2, int value2)
{
	*quote1 = value1;
	*quote2 = value2; ////   esses nomes passam na norma?
}

t_bool	is_inquotes(char *str, char *expansion)
{
	int		quote[3];
	int		d_quote[3];
	int		i;

	ft_bzero(quote, sizeof(quote));
	ft_bzero(d_quote, sizeof(d_quote));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && quote[2] == 0)
			attribute_quotes(&quote[0], i + 1, &quote[2], 1);
		else if (str[i] == '\'' && quote[2] > 0)
			attribute_quotes(&quote[1], i + 1, &quote[2], 0);
		if (str[i] == '\"' && d_quote[2] == 0)
			attribute_quotes(&d_quote[0], i + 1, &d_quote[2], 1);
		else if ((str[i] == '\"' && d_quote[2] > 0))
			attribute_quotes(&d_quote[1], i + 1, &d_quote[2], 0);
		if (str + i == expansion && quote[2] > 0			// se está verificando o indice do '$' && existe uma áspa simples aberta
		&& (!(d_quote[2] > 0 && quote[0] > d_quote[0]))			// not: se existir uma aspa dupla aberta && estiver antes da simples
		&& (!(d_quote[2] == 0 && quote[0] > d_quote[0] && quote[0] < d_quote[1])))		// not: se existir uma aspa dupla fechada && estiver depois da simples
			return (TRUE);
	}
	return (FALSE);
}

static void	print_error(char *error_msg, char error_char)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_msg, 2);
	if (error_char)
	{
		ft_putstr_fd(" `", 2);
		ft_putchar_fd(error_char, 2);
		ft_putchar_fd('`', 2);
	}
	ft_putchar_fd('\n', 2);
}

static void	check_pipe_error(const char *str, t_bool *found_error)
{
	char	*next_cmd;

	next_cmd = ft_strignore(str, BLANK_SPACES);
	if (next_cmd && *next_cmd != '|')
		return ;
	*found_error = TRUE;
	print_error("syntax error near unexpected token", '|');
}

t_bool	cmd_error_parser(const char *cmd_line)
{
	int		i;
	char	quote;
	t_bool	found_error;

	i = 0;
	quote = '\0';
	found_error = FALSE;
	while (cmd_line[i])
	{
		if (quote == '\0' && (cmd_line[i] == '\'' || cmd_line[i] == '\"'))
			quote = cmd_line[i];
		else if (quote != '\0' && cmd_line[i] == quote)
			quote = '\0';
		if (quote == '\0' && cmd_line[i] == '|')
			check_pipe_error(&cmd_line[i + 1], &found_error);
		if (found_error)
			return (found_error);
		i++;
	}
	if (quote != '\0')
	{
		found_error = TRUE;
		print_error("syntax error from unclosed quotes", quote);
	}
	return (found_error);
}
