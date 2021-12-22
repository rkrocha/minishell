/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:53:06 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/22 15:13:42 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_from_pipe(int fd)
{
	char	*str;

	while (TRUE)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		ft_putstr(str);
		free(str);
	}
}

static void	cmd_exec_single(t_shell *minishell, t_cmd *current)
{
	static int (*const	func_ptr[8])(t_shell *, t_cmd *) = {
		msh_execve, msh_cd, msh_echo, msh_env,
		msh_exit, msh_export, msh_pwd, msh_unset};
	int					redir[2];
	int					clone_in;
	int					clone_out;

	ft_bzero(redir, 2 * sizeof(int));
	redirect(minishell, current, redir);
	if (redir[0] < 0)
	{
		minishell->last_return = 130;
		return ;
	}
	if (redir[0] > 0)
	{
		clone_in = dup(0);
		dup2(redir[0], 0);
	}
	if (redir[1] > 0)
	{
		clone_out = dup(1);
		dup2(redir[1], 1);
		close(redir[1]);
	}
	minishell->last_return = func_ptr[current->type](minishell, current);
	if (redir[0] > 0)
	{
		close(redir[0]);
		dup2(clone_in, 0);
		close(clone_in);
	}
	if (redir[1] > 0)
	{
		dup2(clone_out, 1);
		close(clone_out);
	}
	// int fd1 = open("/dev/tty", O_RDONLY);
	// dup2(fd1, 0);
	// close(fd1);
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
	int		redir[2];
	int		status;

	ft_bzero(redir, 2 * sizeof(int));
	clone_in = dup(0);
	pipe(msh->ret_fd);
	while (tracker && WEXITSTATUS(status) != 130)
	{
		current = ((t_cmd *)tracker->content);
		pipe(msh->data_fd);
		pid = fork();
		if (pid == 0)
		{
			redirect(msh, current, redir);
			if (redir[0] < 0)
			{
				write(msh->ret_fd[1], &redir[0], sizeof(int));
				exit(130);
			}
			if (redir[0])
				dup2(redir[0], 0);
			if (!redir[1])
				redir[1] = msh->data_fd[1];
			dup2(redir[1], 1);
			close(msh->data_fd[0]);
			close(msh->data_fd[1]);
			cmd_exec_pipes(msh, current);
		}
		// wait(NULL);
		waitpid(pid, &status, WUNTRACED);
		read(msh->ret_fd[0], &msh->last_return, sizeof(msh->last_return));
		if (WEXITSTATUS(status) == 130)
			msh->last_return = 130;
		if (msh->last_return != 130 && tracker->next && !((t_cmd *)tracker->next->content)->input)
		{
			dup2(msh->data_fd[0], 0);
			close(msh->data_fd[0]);
		}
		close(msh->data_fd[1]);
		tracker = tracker->next;
	}
	if (msh->last_return != 130)
		print_from_pipe(msh->data_fd[0]);
	close(msh->data_fd[0]);
	close(msh->data_fd[1]);
	close(msh->ret_fd[0]);
	close(msh->ret_fd[1]);
	close(redir[0]);
	dup2(clone_in, 0);
	close(clone_in);
}

void	cmd_router(t_shell *minishell)
{
	t_list	*tracker;

	signal(SIGINT, SIG_IGN);
	tracker = minishell->cmd_list;
	if (!tracker->next)
		cmd_exec_single(minishell, ((t_cmd *)tracker->content));
	else
		cmd_exec_pipes_iter(minishell, tracker);
	signal(SIGINT, sigint);
}
