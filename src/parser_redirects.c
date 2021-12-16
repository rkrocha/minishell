/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:46:34 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/16 14:06:12 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_redirects(char *cmd_line)
{
	int		count;
	char	*tracker;

	count = 0;
	tracker = cmd_line;
	while (tracker)
	{
		tracker = ft_strsearch(tracker, "<>");
		if (!tracker)
			break ;
		if (tracker && is_inquotes(cmd_line, tracker) == 0)
			count++;
		tracker++;
		if (tracker && ft_strchr("<>", *tracker))
			tracker++;
	}
	return (count);
}

char	*divide_redirects(char *cmd)
{
	char	*new_cmd;
	int		new_size;
	int		reader;
	int		printer;

	new_size = ft_strlen(cmd) + (count_redirects(cmd) * 2) + 1;
	new_cmd = malloc(new_size * sizeof(char));
	reader = 0;
	printer = 0;
	printf("old cmd: %s // %d\n", cmd, new_size);
	while (cmd[reader])
	{
		if (ft_strchr("<>", cmd[reader]) && !is_inquotes(cmd, &cmd[reader]))
		{
			new_cmd[printer++] = ' ';
			new_cmd[printer++] = cmd[reader++];
			if (cmd[reader] && ft_strchr("<>", cmd[reader]))
				new_cmd[printer++] = cmd[reader++];
			new_cmd[printer++] = ' ';
		}
		if (!cmd[reader])
			break ;
		new_cmd[printer++] = cmd[reader++];
	}
	new_cmd[printer] = '\0';
	printf("new cmd: %s\n", new_cmd);
	return (new_cmd);
}

// static int	find_redirect(char *arg)
// {

// }

// void	cmd_redirects_parser(t_shell *minishell, t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd->argv[i])
// 	{
// 		find_redirect(cmd->argv[i]);
// 		i++;
// 	}
// }

// <<< redireciona string para input: fora do escopo (erro)

/*
**	arg por arg em argv: buscar redirect
**		colher informações e checar erros
**	Se não tiver erros, remover args do argv que são redirects ou args de redirs
*/
