/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:53:06 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/14 12:22:38 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_exec(t_shell *minishell, t_cmd *current)
{
	static int (*const	func_ptr[8])(t_shell *, t_cmd *) = {
		msh_execve, msh_cd, msh_echo, msh_env,
		msh_exit, msh_export, msh_pwd, msh_unset};
	int					ret;

	ret = func_ptr[current->type](minishell, current);
	write(minishell->ret_fd[1], &ret, sizeof(ret));
	exit(0);
}

void	cmd_router(t_shell *msh)
{
	t_list	*tracker;
	t_cmd	*current;
	int		pid;
	int		clone_in;

	char	buffer[512];

	clone_in = dup(0);
	tracker = msh->cmd_list;
	pipe(msh->ret_fd);
	while (tracker)
	{
		current = ((t_cmd *)tracker->content);
		pipe(msh->data_fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(msh->data_fd[1], 1);
			close(msh->data_fd[0]);
			close(msh->data_fd[1]);
			cmd_exec(msh, current);
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
	// close(0);
	// exit(0);
}
