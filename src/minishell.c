/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:53:43 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/23 11:09:247 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CYELLOW "\001\e[0;34m\002"
#define RESET   "\001\e[0m\002"

void	get_prompt(t_shell *msh)
{
	char	**strs;

	free(msh->prompt);
	strs = ft_calloc(5, sizeof(char *));
	strs[0] = get_env(msh, "LOGNAME");
	strs[1] = get_env(msh, "PWD");
	strs[2] = get_env(msh, "HOME");
	if (ft_strncmp(strs[1], strs[2], ft_strlen(strs[2]) + 1) == 0)
		strs[3] = ft_strdup("~");
	else if (ft_strncmp(strs[1], "/", 2) == 0)
		strs[3] = ft_strdup("/");
	else
		strs[3] = ft_strjoin("", ft_strrchr(strs[1], '/') + 1);
	// msh->prompt = ft_strjoin("\e[34m", strs[0]);										// usuario
	// msh->prompt = ft_strjoin_free(&msh->prompt, " \e[m\e[36m");
	// msh->prompt = ft_strjoin_free(&msh->prompt, strs[3]);                      				 // dir
	// msh->prompt = ft_strjoin_free(&msh->prompt, "\e[m\e[32m $\e[m ");		// $
	// msh->prompt = ft_strdup(strs[0]);										// usuario
	msh->prompt = ft_strjoin("\001\e[0;34m\002", strs[0]);										// usuario
	msh->prompt = ft_strjoin_free(&msh->prompt, " ");
	msh->prompt = ft_strjoin_free(&msh->prompt, strs[3]);                      				 // dir
	msh->prompt = ft_strjoin_free(&msh->prompt, " $\001\e[0m\002 ");		// $
	ft_split_free(&strs);
}

// export PS1="[\[\e[34m\]\u\[\e[m\] \[\e[36m\]\W\[\e[m\]] \[\e[32m\]\\$\[\e[m\] "

static void	handle_cmd(t_shell *minishell)
{
	char	*cmd_line;

	minishell->end = check_input();
	get_prompt(minishell);
	cmd_line = readline(minishell->prompt);
	// cmd_line = readline(CYELLOW "P> " RESET);
	if (!cmd_line)
		free_and_exit(minishell, minishell->last_return);
	if (!*cmd_line || !ft_strignore(cmd_line, BLANK_SPACES))
	{
		free(cmd_line);
		return ;
	}
	add_history(cmd_line);
	if (cmd_error_parser(cmd_line) == FALSE)
	{
		cmd_parser(minishell, cmd_line);
		ft_strdel(&cmd_line);
		cmd_router(minishell);
		ft_lstclear(&minishell->cmd_list, del_cmd);
	}
	free(cmd_line);
}

void	sigint(int signum)
{
	rl_on_new_line();
	ft_putchar('\n');
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

int	main(int argc, const char **argv, const char **envp)
{
	t_shell	minishell;

	(void)argc;
	(void)argv;
	ft_bzero(&minishell, sizeof(minishell));
	init_env(&minishell, envp);
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
	while (!minishell.end)
		handle_cmd(&minishell);
	// printf("%i\n", minishell.last_return); ///// remover
	free_and_exit(&minishell, minishell.last_return);
}
