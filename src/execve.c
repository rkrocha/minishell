/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:00:46 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/09 18:10:49 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_shell *minishell, t_cmd *cmd)
{
	char	*var_path;
	char	**path_list;
	char	*cmd_path;
	int		i;

	if (cmd->argv[0][0] == '.')
		return (ft_strdup(cmd->argv[0]));
	var_path = get_env(minishell, "PATH");
	path_list = ft_split(var_path, ':');
	i = -1;
	while (path_list[++i])
	{
		cmd_path = ft_strjoin(path_list[i], "/");
		cmd_path = ft_strjoin_free(&cmd_path, cmd->argv[0]);
		if (!access(cmd_path, F_OK))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_split_free(&path_list);
	free(var_path);
	return (cmd_path);
}

static int	get_err(char *cmd, int err_n)
{
	char	*err;

	err = ft_strdup("minishell: ");
	err = ft_strjoin_free(&err, cmd);
	if (err_n == 0)
		err = ft_strjoin_free(&err, ": command not found");
	else
	{
		err = ft_strjoin_free(&err, ": ");
		err = ft_strjoin_free(&err, strerror(errno));
	}
	ft_putendl(err);
	free (err);
	if (err_n == 0)
		return (127);
	else
		return (126);
}

int	msh_execve(t_shell *minishell, t_cmd *cmd)
{
	pid_t	pid;
	char	*cmd_path;
	int		status;
	char	buffer[4];
	int		fd[2];

	cmd_path = get_path(minishell, cmd);
	if (!cmd_path)
		cmd->return_value = get_err(cmd->argv[0], 0);
	else
	{
		status = pipe(fd);
		free(cmd->argv[0]);
		cmd->argv[0] = cmd_path;
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			if (execve(cmd->argv[0], cmd->argv, minishell->env))
				ft_putnbr_fd(get_err(cmd->argv[0], errno), fd[1]);
			exit (0);
		}
		else
		{	
			close(fd[1]);
			read(fd[0], buffer, 4);
			cmd->return_value = ft_atoi(buffer);
			waitpid(pid, &status, WUNTRACED);
		}
	}
	return (cmd->return_value);
}
