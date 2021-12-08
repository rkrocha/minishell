/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:04:02 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/08 14:24:55 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_quotes_parser(char *arg)
{
	int		reader;
	int		printer;
	char	quote;

	reader = -1;
	printer = 0;
	quote = '\0';
	while (arg[++reader])
	{
		if (quote == '\0' && (arg[reader] == '\'' || arg[reader] == '\"'))
		{
			quote = arg[reader];
			continue ;
		}
		else if (quote != '\0' && arg[reader] == quote)
		{
			quote = '\0';
			continue ;
		}
		arg[printer] = arg[reader];
		printer++;
	}
	arg[printer] = '\0';
}

void	cmd_quotes_parser(t_cmd *cmd)
{
	char	**argv;

	argv = cmd->cmd_v;
	while (*argv)
	{
		// printf("ORIGINAL_ARG: %s\n", *argv); //////////
		arg_quotes_parser(*argv);
		// printf("UNQUOTED_ARG: %s\n\n", *argv); ////////
		argv++;
	}
}


// ls "'$HOME'" '"$HOME"' "'""'" "" '' "hello" "'''" '""$HOME' abc"123" 'abc'123 "abc"$HOME abc"$HOME"abc
