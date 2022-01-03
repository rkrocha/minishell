/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:53:43 by rkochhan          #+#    #+#             */
/*   Updated: 2022/01/03 13:50:02 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(t_shell *msh)
{
	char	**strs;

	free(msh->prompt);
	strs = ft_calloc(5, sizeof(char *));
	strs[0] = get_env(msh, "STUDENT_LOGIN");
	strs[1] = get_env(msh, "PWD");
	strs[2] = get_env(msh, "HOME");
	if (ft_strncmp(strs[1], strs[2], ft_strlen(strs[2]) + 1) == 0)
		strs[3] = ft_strdup("~");
	else if (ft_strncmp(strs[1], "/", 2) == 0)
		strs[3] = ft_strdup("/");
	else
		strs[3] = ft_strjoin("", ft_strrchr(strs[1], '/') + 1);
	msh->prompt = ft_strjoin("\001\e[0;34m\002", strs[0]);
	msh->prompt = ft_strjoin_free(&msh->prompt, " ");
	msh->prompt = ft_strjoin_free(&msh->prompt, strs[3]);
	msh->prompt = ft_strjoin_free(&msh->prompt, " $\001\e[0m\002 ");
	ft_split_free(&strs);
}

static void	handle_cmd(t_shell *minishell)
{
	char	*cmd_line;

	minishell->end = check_input();
	get_prompt(minishell);
	cmd_line = readline(minishell->prompt);
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
	free_and_exit(&minishell, minishell.last_return);
}
