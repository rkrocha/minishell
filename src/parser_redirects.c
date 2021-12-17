/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:46:34 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/17 13:33:38 by rkochhan         ###   ########.fr       */
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
	// printf("old cmd: %s // %d\n", cmd, new_size);
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
	// printf("new cmd: %s\n", new_cmd);
	return (new_cmd);
}

static void	get_redirect(t_cmd *cmd, char **redir, char **arg)
{
	t_list	**chosen_redir;
	char	*redir_type;
	char	*redir_str;

	chosen_redir = &cmd->output;
	if (*redir[0] == '<')
		chosen_redir = &cmd->input;
	redir_type = ft_itoa(ft_strlen(*redir));
	arg_quotes_parser(*arg);
	redir_str = ft_strjoin(redir_type, *arg);
	free(redir_type);
	ft_strdel(redir);
	ft_strdel(arg);
	ft_lstadd_back(chosen_redir, ft_lstnew(redir_str));
}

static int	cat_argv(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		if (argv[i] == NULL)
		{
			while (i + j < argc && argv[i + j] == NULL)
				j++;
			if (i + j >= argc)
				break ;
			argv[i] = argv[i + j];
			argv[i + j] = NULL;
		}
		i++;
	}
	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

void	cmd_redirects_parser(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '<' || cmd->argv[i][0] == '>')
		{
			get_redirect(cmd, &cmd->argv[i], &cmd->argv[i + 1]);
			i++;
		}
		i++;
	}
	cmd->argc = cat_argv(cmd->argc, cmd->argv);



	// t_list	*tracker;
	// printf("Argc: %i\n", cmd->argc);
	// printf("Input:\n");
	// tracker = cmd->input;
	// while (tracker)
	// {
	// 	printf("%s\n", (char *)tracker->content);
	// 	tracker = tracker->next;
	// }
	// printf("\nOutput:\n");
	// tracker = cmd->output;
	// while (tracker)
	// {
	// 	printf("%s\n", (char *)tracker->content);
	// 	tracker = tracker->next;
	// }
	// printf("______________\n");
}

// 2EOF
// 1"file.txt"
// <<< redireciona string para input: fora do escopo (erro)

/*
**	arg por arg em argv: buscar redirect
**		colher informações e checar erros
**	Se não tiver erros, remover args do argv que são redirects ou args de redirs
**	Atualizar o argc


** TIRAR AS ASPAS
** CHECAR ARG NULO
*/
