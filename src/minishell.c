/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:53:43 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/20 14:12:33 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(t_shell *minishell)
{
	char	*user;
	char	*host;
	char	*pwd;
	char	*dir;
	char	*home;

	user = get_env(minishell, "LOGNAME");
	host = get_env(minishell, "NAME");
	pwd = get_env(minishell, "PWD");
	home = get_env(minishell, "HOME");
	if (ft_strncmp(pwd, home, ft_strlen(home) + 1) == 0)
		dir = ft_strdup("~");
	else if (ft_strncmp(pwd, "/", 2) == 0)
		dir = ft_strdup("/");
	else
		dir = ft_strjoin("", ft_strrchr(pwd, '/') + 1);
	printf("[\e[34m%s@%s\e[00m \e[36m%s\e[00m]", user, host, dir);
	free(user);
	free(host);
	free(pwd);
	free(home);
	free(dir);
}

static void	handle_cmd(t_shell *minishell)
{
	char	*cmd_line;

	minishell->end = check_input();
	get_prompt(minishell);
	cmd_line = readline("\e[32m$\e[00m ");
	if (!cmd_line || !*cmd_line)
	{
		free(cmd_line);
		return ;
	}
	add_history(cmd_line);
	if (cmd_error_parser(cmd_line) == FALSE)
	{
		cmd_parser(minishell, cmd_line);
		cmd_router(minishell);
		ft_lstclear(&minishell->cmd_list, del_cmd);
	}
	free(cmd_line);
	// int fd1 = open("/dev/tty", O_RDONLY);
	// dup2(fd1, 0);
	// close(fd1);
	// int fd2 = open("/dev/pts/1", O_WRONLY);
	// dup2(fd2, 1);
	// dup2(fd2, 2);
	// close(fd2);
}

int	main(int argc, const char **argv, const char **envp)
{
	t_shell	minishell;

	(void)argc;
	(void)argv;
	// definições de sinais?
	ft_bzero(&minishell, sizeof(minishell));
	init_env(&minishell, envp);
	while (!minishell.end)
		handle_cmd(&minishell);
	printf("%i\n", minishell.last_return); ///// remover
	rl_clear_history();			// juntar todos clears e frees em uma só função?
	ft_split_free(&minishell.env);
	free(minishell.home);
	free(minishell.pwd);
	return (minishell.last_return);
}
