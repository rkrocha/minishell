/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:39:28 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/28 14:41:44 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input(char *file_name)
{
	struct stat	buffer;
	int			fd;

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

static int	redirect_input(t_shell *msh, t_list *input)
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
			fd = open_input(file_name);
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

static int	open_output(char *file_name, int type)
{
	struct stat	buffer;
	int			fd;

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

static int	redirect_output(t_list *output)
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
