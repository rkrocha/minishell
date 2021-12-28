/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:29:06 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/28 13:28:21 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_shell *minishell, int return_value)
{
	rl_clear_history();
	ft_split_free(&minishell->env);
	ft_lstclear(&minishell->cmd_list, del_cmd);
	free(minishell->home);
	free(minishell->pwd);
	free(minishell->prompt);
	exit(return_value);
}

void	del_cmd(void *elem)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)elem;
	ft_split_free(&cmd->argv);
	ft_lstclear(&cmd->input, free);
	ft_lstclear(&cmd->output, free);
	free(cmd);
}

int	throw_err(char *cmd, int err_n)
{
	char	*err;
	int		ret_no;

	err = ft_strdup("minishell: ");
	err = ft_strjoin_free(&err, cmd);
	if (err_n == 0)
		err = ft_strjoin_free(&err, ": command not found");
	else if (err_n == -1)
		err = ft_strjoin_free(&err, ": No such file or directory");
	else if (err_n == -2)
		err = ft_strjoin_free(&err, ": Is a directory");
	else if (err_n == -3)
		err = ft_strjoin_free(&err, ": Permission denied");
	else
	{
		err = ft_strjoin_free(&err, ": ");
		err = ft_strjoin_free(&err, strerror(errno));
	}
	ft_putendl(err);
	free (err);
	ret_no = 126;
	if (err_n == 0 || err_n == -1)
		ret_no = 127;
	return (ret_no);
}

void	sigint(int signum)
{
	rl_on_new_line();
	ft_putchar('\n');
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}
