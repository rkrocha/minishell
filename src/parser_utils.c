/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:04:03 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/12 09:13:13 by rkochhan         ###   ########.fr       */
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
