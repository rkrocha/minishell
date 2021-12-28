/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:53:06 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/28 13:50:57 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fd_handler(t_shell *msh, int *redir, int *clone)
{
	if (redir[0] < 0)
	{
		msh->last_return = 130;
		return (-1);
	}
	if (redir[1] < 0)
	{
		msh->last_return = 1;
		return (-1);
	}
	if (redir[0] > 0)
	{
		clone[0] = dup(0);
		dup2(redir[0], 0);
	}
	if (redir[1] > 0)
	{
		clone[1] = dup(1);
		dup2(redir[1], 1);
		close(redir[1]);
	}
	return (0);
}

static void	fd_restore(int *redir, int *clone)
{
	if (redir[0] > 0)
	{
		close(redir[0]);
		dup2(clone[0], 0);
		close(clone[0]);
	}
	if (redir[1] > 0)
	{
		dup2(clone[1], 1);
		close(clone[1]);
	}
}

static void	cmd_exec_single(t_shell *minishell, t_cmd *current)
{
	static int (*const	func_ptr[9])(t_shell *, t_cmd *) = {
		msh_execve, msh_cd, msh_echo, msh_env,
		msh_exit, msh_export, msh_pwd, msh_unset, msh_dummy};
	int					redir[2];
	int					clone[2];

	ft_bzero(redir, 2 * sizeof(int));
	redirect(minishell, current, redir);
	if (fd_handler(minishell, redir, clone) == -1)
		return ;
	minishell->last_return = func_ptr[current->type](minishell, current);
	fd_restore(redir, clone);
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
