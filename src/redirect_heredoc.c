/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:40:18 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/29 15:27:36 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_free(t_shell *msh)
{
	static t_shell	*ptr;

	if (msh)
		ptr = msh;
	else
		free_and_exit(ptr, 130);
}

static void	sigexit(int signum)
{
	(void)signum;
	ft_putchar('\n');
	sig_free(NULL);
}

static void	error_eof(char *delim)
{
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here_document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putendl_fd("`)", 2);
}

static void	here_doc_read(t_shell *msh, int *fildes, char *delim)
{
	char	*str;

	close(fildes[0]);
	sig_free(msh);
	signal(SIGINT, sigexit);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			error_eof(delim);
			break ;
		}
		if (!ft_strncmp(str, delim, ft_strlen(delim) + 1))
		{
			free(str);
			break ;
		}
		str = ft_strjoin_free(&str, "\n");
		write(fildes[1], str, ft_strlen(str));
		free(str);
	}
	close(fildes[1]);
	free_and_exit(msh, 0);
}

int	here_doc(t_shell *msh, char *delim)
{
	int		fildes[2];
	int		status;
	int		pid;

	pipe(fildes);
	pid = fork();
	if (pid == 0)
		here_doc_read(msh, fildes, delim);
	waitpid(pid, &status, WUNTRACED);
	if (WEXITSTATUS(status) == 130)
	{
		close(fildes[0]);
		fildes[0] = -1;
	}
	close(fildes[1]);
	return (fildes[0]);
}
