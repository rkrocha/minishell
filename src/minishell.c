/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:53:43 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/02 14:25:5:44 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, const char **argv, const char **envp)
{
	t_shell	minishell;
	char	*cmd;

	(void)argc;
	(void)argv;
	// definições de sinais?
	ft_bzero(&minishell, sizeof(minishell));
	minishell.env = (char **)envp;
	while (!minishell.end)
	{
		cmd = readline("\e[32m$\e[00m ");
		if (!cmd || !*cmd)
		{
			free(cmd);
			continue ;
		}
		add_history(cmd);				// chama o parser
		cmd_parser(&minishell, cmd);	// executar comandos
		cmd_router(&minishell);
		ft_lstclear(&minishell.cmd_list, del_cmd);
		free(cmd);
	}
	rl_clear_history();
	return (minishell.last_return);
}
