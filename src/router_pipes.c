/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:31:53 by rkochhan          #+#    #+#             */
/*   Updated: 2022/01/03 11:57:16 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fd_close_restore(t_shell *msh, int *redir, int clone_in)
{
	close(msh->data_fd[0]);
	close(msh->data_fd[1]);
	close(msh->ret_fd[0]);
	close(msh->ret_fd[1]);
	close(redir[0]);
	close(redir[1]);
	dup2(clone_in, 0);
	close(clone_in);
}

static void	cmd_exec_pipes(t_shell *minishell, t_cmd *current)
{
	static int (*const	func_ptr[9])(t_shell *, t_cmd *) = {
		msh_execve, msh_cd, msh_echo, msh_env,
		msh_exit, msh_export, msh_pwd, msh_unset, msh_dummy};
	int					ret;

	close(minishell->ret_fd[0]);
	ret = func_ptr[current->type](minishell, current);
	write(minishell->ret_fd[1], &ret, sizeof(ret));
	close(minishell->ret_fd[1]);
	free_and_exit(minishell, 0);
}

static void	exec_in_child_process(t_shell *msh, t_cmd *current, int *redir)
{
	redirect(msh, current, redir);
	if (redir[0] < 0)
	{
		write(msh->ret_fd[1], &redir[0], sizeof(int));
		close(msh->ret_fd[0]);
		close(msh->ret_fd[1]);
		free_and_exit(msh, 130);
	}
	if (redir[1] < 0)
	{
		write(msh->ret_fd[1], &redir[1], sizeof(int));
		close(msh->ret_fd[0]);
		close(msh->ret_fd[1]);
		free_and_exit(msh, 1);
	}
	if (redir[0])
		dup2(redir[0], 0);
	if (!redir[1])
		redir[1] = msh->data_fd[1];
	dup2(redir[1], 1);
	close(msh->data_fd[1]);
	close(msh->data_fd[0]);
	cmd_exec_pipes(msh, current);
}

static void	pipes_handler(t_shell *msh, t_list *tracker, int status)
{
	if (WEXITSTATUS(status) == 130)
		msh->last_return = 130;
	if (msh->last_return != 130 && tracker->next
		&& !((t_cmd *)tracker->next->content)->input)
		dup2(msh->data_fd[0], 0);
	close(msh->data_fd[1]);
}

void	cmd_exec_pipes_iter(t_shell *msh, t_list *tracker)
{
	t_cmd	*current;
	int		pid;
	int		clone_in;
	int		redir[2];
	int		status;

	ft_bzero(redir, 2 * sizeof(int));
	status = 0;
	clone_in = dup(0);
	pipe(msh->ret_fd);
	while (tracker && WEXITSTATUS(status) != 130)
	{
		current = ((t_cmd *)tracker->content);
		pipe(msh->data_fd);
		pid = fork();
		if (pid == 0)
			exec_in_child_process(msh, current, redir);
		waitpid(pid, &status, WUNTRACED);
		read(msh->ret_fd[0], &msh->last_return, sizeof(msh->last_return));
		pipes_handler(msh, tracker, status);
		tracker = tracker->next;
	}
	if (msh->last_return != 130)
		print_from_pipe(msh->data_fd[0]);
	fd_close_restore(msh, redir, clone_in);
}
