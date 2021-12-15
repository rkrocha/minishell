/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:53:06 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/14 13:35:01 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_exec_single(t_shell *minishell, t_cmd *current)
{
	static int (*const	func_ptr[8])(t_shell *, t_cmd *) = {
		msh_execve, msh_cd, msh_echo, msh_env,
		msh_exit, msh_export, msh_pwd, msh_unset};

	minishell->last_return = func_ptr[current->type](minishell, current);
}

static void	cmd_exec_pipes(t_shell *minishell, t_cmd *current)
{
	static int (*const	func_ptr[8])(t_shell *, t_cmd *) = {
		msh_execve, msh_cd, msh_echo, msh_env,
		msh_exit, msh_export, msh_pwd, msh_unset};
	int					ret;

	ret = func_ptr[current->type](minishell, current);
	write(minishell->ret_fd[1], &ret, sizeof(ret));
	exit(0);
}

static void	cmd_exec_pipes_iter(t_shell *msh, t_list *tracker)
{
	t_cmd	*current;
	int		pid;
	int		clone_in;
	char	buffer[512];
	
	clone_in = dup(0);
	pipe(msh->ret_fd);
	while (tracker)
	{
		current = ((t_cmd *)tracker->content);
		pipe(msh->data_fd);
		pid = fork();
		if (pid == 0)
		{
			// caso haja um redirect de entrada
			// open("[]");
			// caso haja um redirect de saída
			dup2(msh->data_fd[1], 1);
			close(msh->data_fd[0]);
			close(msh->data_fd[1]);
			cmd_exec_pipes(msh, current);
		}
		wait(NULL);
		read(msh->ret_fd[0], &msh->last_return, sizeof(msh->last_return));
		dup2(msh->data_fd[0], 0);
		close(msh->data_fd[1]);
		tracker = tracker->next;
	}
	read(msh->data_fd[0], buffer, 512);
	buffer[511] = '\0';
	printf("%s", buffer);
	close(msh->data_fd[0]);
	close(msh->data_fd[1]);
	close(msh->ret_fd[0]);
	close(msh->ret_fd[1]);
	dup2(clone_in, 0);
}

void	cmd_router(t_shell *minishell)
{
	t_list	*tracker;

	tracker = minishell->cmd_list;
	if (!tracker->next)
		cmd_exec_single(minishell, ((t_cmd *)tracker->content));
	else
		cmd_exec_pipes_iter(minishell, tracker);
}
