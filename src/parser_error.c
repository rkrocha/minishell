/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:59:40 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/16 14:51:55 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	check_quote_error(const char quote, t_bool *found_error)
{
	if (quote == '\0')
		return ;
	*found_error = TRUE;
	print_error("syntax error from unclosed quotes", quote);
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

static void	check_redirect_error(const char *str, t_bool *found_error)
{
	int	redir_len;

	redir_len = 0;
	while (str[redir_len] && (str[redir_len] == '<' || str[redir_len] == '>'))
		redir_len++;
	if (redir_len == 1 || (redir_len == 2 && str[0] == str[1]))
		return ;
	*found_error = TRUE;
	print_error("syntax error near unexpected token", str[0]);
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
		if (quote == '\0' && (cmd_line[i] == '<' || cmd_line[i] == '>'))
			check_redirect_error(&cmd_line[i], &found_error);
		if (found_error)
			return (found_error);
		i++;
	}
	check_quote_error(quote, &found_error);
	return (found_error);
}
