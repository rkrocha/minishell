/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:46:34 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/16 13:33:21 by dpiza            ###   ########.fr       */
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

char	*divide_redirects(char *cmd_line)
{
	char	*new_cmd_line;
	int		new_size;
	int		reader;
	int		printer;

	new_size = ft_strlen(cmd_line) + (count_redirects(cmd_line) * 2) + 1;
	new_cmd_line = malloc(new_size * sizeof(char));
	reader = 0;
	printer = 0;
	printf("old cmd: %s // %d\n", cmd_line, new_size);
	while (cmd_line[reader])
	{
		if (ft_strchr("<>", cmd_line[reader]) && !is_inquotes(cmd_line, &cmd_line[reader]))
		{
			new_cmd_line[printer++] = ' ';
			new_cmd_line[printer++] = cmd_line[reader++];
			if (ft_strchr("<>", cmd_line[reader]))
				new_cmd_line[printer++] = cmd_line[reader++];
			new_cmd_line[printer++] = ' ';
		}
		if (!cmd_line[reader])
			break ;
		new_cmd_line[printer++] = cmd_line[reader++];
	}
	new_cmd_line[printer] = '\0';
	printf("new cmd: %s\n", new_cmd_line);
	return (new_cmd_line);
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
**			se tiver redirect, verificar se está dentro de aspas
**		caso contrário, colher informações e checar erros
**	Se não tiver erros, remover args do argv que são redirects ou args de redirs
*/