/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:39:28 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/20 15:45:01 by dpiza            ###   ########.fr       */
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

static int	here_doc(char *delim)
{
	char	*str;
	char	*actual_delim;
	int		fildes[2];

	actual_delim = ft_strjoin(delim, "\n");
	pipe(fildes);
	while (1)
	{
		str = get_next_line(0);
		if (!str)
		{
			ft_putstr_fd("here_document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delim, 2);
			ft_putendl_fd("`)", 2);
			break ;
		}
		if (!ft_strncmp(str, actual_delim, ft_strlen(actual_delim)))
		{
			free(str);
			break ;
		}
		write(fildes[1], str, ft_strlen(str));
		free(str);
	}
	close(fildes[1]);
	free(actual_delim);
	return (fildes[0]);
}

int		redirect_input(t_list *input)
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
			fd = here_doc(file_name);
		if (fd < 0)
			break ;
		tracker = tracker->next;
	}
	return (fd);
}

int	open_output(char *file_name, int type)
{
	
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
	}
	return (fd);
}

void	redirect(t_cmd *cmd, int *redir)
{
	redir[0] = redirect_input(cmd->input);
	redir[1] = redirect_output(cmd->output);
}