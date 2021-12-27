/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:39:28 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/27 15:11:49 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(char *file_name)
{
	struct stat	buffer;
	int	fd;

	fd = -1;
	stat(file_name, &buffer);
	if (access(file_name, F_OK))
		throw_err(file_name, -1);
	else if (access(file_name, R_OK))
		throw_err(file_name, -3);
	else if (buffer.st_mode == 16877)
		throw_err(file_name, -2);
	else
		fd = open(file_name, O_RDONLY);
	return (fd);
}

static void	sigexit(int signum)
{
	(void)signum;
	ft_putchar('\n');
	exit(130);
}

static int	here_doc(t_shell *msh, char *delim)
{
	char	*str;
	// char	*actual_delim;
	int		fildes[2];
	int		status;
	int		pid;

	// actual_delim = ft_strjoin(delim, "\n");
	pipe(fildes);
	pid = fork();
	if (pid == 0)
	{
		close(fildes[0]);
		signal(SIGINT, sigexit);
		while (1)
		{
			str = readline("> ");
			if (!str)
			{
				ft_putstr_fd("minishell: warning: here_document delimited by end-of-file (wanted `", 2);
				ft_putstr_fd(delim, 2);
				ft_putendl_fd("`)", 2);
				break ;
			}
			// if (!ft_strncmp(str, actual_delim, ft_strlen(actual_delim)))
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
	waitpid(pid, &status, WUNTRACED);
	if (WEXITSTATUS(status) == 130)
		fildes[0] = -1;
	close(fildes[1]);
	// free(actual_delim);
	return (fildes[0]);
}

int		redirect_input(t_shell *msh, t_list *input)
{
	t_list	*tracker;
	int		type;
	char	*file_name;
	int		fd;

	if (!input)
		return (0);
	tracker = input;
	while (tracker)
	{
		type = ((char *)tracker->content)[0] - 48;
		file_name = &((char *)tracker->content)[1];
		if (type == 1)
			fd = open_file(file_name);
		else
			fd = here_doc(msh, file_name);
		if (fd < 0)
			break ;
		tracker = tracker->next;
		if (tracker)
			close(fd);
	}
	return (fd);
}

int	open_output(char *file_name, int type)
{
	struct stat	buffer;
	int		fd;

	fd = -1;
	if (!stat(file_name, &buffer) && buffer.st_mode == 16877)
		throw_err(file_name, -2);
	else if (!access(file_name, F_OK) && access(file_name, W_OK))
		throw_err(file_name, -3);
	if (type == 1)
		fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (type == 2)
		fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

int		redirect_output(t_list *output)
{
	t_list	*tracker;
	int		type;
	char	*file_name;
	int		fd;

	if (!output)
		return (0);
	tracker = output;
	while (tracker)
	{
		type = ((char *)tracker->content)[0] - 48;
		file_name = &((char *)tracker->content)[1];
		fd = open_output(file_name, type);
		if (fd < 0)
			break ;
		tracker = tracker->next;
		if (tracker)
			close(fd);
	}
	return (fd);
}

void	redirect(t_shell *msh, t_cmd *cmd, int *redir)
{
	redir[0] = redirect_input(msh, cmd->input);
	if (redir[0] == -1)
		return ;
	redir[1] = redirect_output(cmd->output);
}
