/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:53:43 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/03 15:01:11 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, const char **argv, const char **envp)
{
	t_shell	minishell;
	char	*cmd_line;

	(void)argc;
	(void)argv;
	// definições de sinais?
	ft_bzero(&minishell, sizeof(minishell));
	init_env(&minishell, envp);
	while (!minishell.end)
	{
		cmd_line = readline("\e[32m$\e[00m ");
		if (!cmd_line || !*cmd_line)
		{
			free(cmd_line);
			continue ;
		}
		add_history(cmd_line);				// chama o parser
		cmd_parser(&minishell, cmd_line);	// executar comandos
		cmd_router(&minishell);
		ft_lstclear(&minishell.cmd_list, del_cmd);
		free(cmd_line);
	}
	rl_clear_history();
	free_env(&minishell.env);
	return (minishell.last_return);
}
