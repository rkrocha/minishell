/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:00:46 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/23 13:50:005 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*get_path(t_shell *msh, t_cmd *cmd)
{
	char	*var_path;
	char	**path_list;
	char	*cmd_path;
	int		i;

	var_path = get_env(msh, "PATH");
	path_list = ft_split(var_path, ':');
	i = -1;
	while (path_list[++i])
	{
		cmd_path = ft_strjoin(path_list[i], "/");
		cmd_path = ft_strjoin_free(&cmd_path, cmd->argv[0]);
		if (!access(cmd_path, F_OK & X_OK))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_split_free(&path_list);
	free(var_path);
	return (cmd_path);
}

static char	*get_cmd_path(t_shell *msh, t_cmd *cmd)
{
	char		*cmd_path;
	struct stat	buffer;

	if (ft_strncmp(*cmd->argv, "./", 2) == 0)
	{
		stat(cmd->argv[0], &buffer);
		if (access(cmd->argv[0], F_OK))
			cmd->return_value = throw_err(cmd->argv[0], -1);
		else if (buffer.st_mode == 16877)
			cmd->return_value = throw_err(cmd->argv[0], -2);
		else
			return (ft_strdup(cmd->argv[0]));
		return (NULL);
	}
	cmd_path = get_path(msh, cmd);
	if (!cmd_path)
		cmd->return_value = throw_err(cmd->argv[0], 0);
	return (cmd_path);
}

void	sigprint(int n)
{
	(void)n;
	printf("Cancelou!!!!!!\n");
}

static void	exec_cmd(t_shell *msh, t_cmd *cmd, int *fd)
{
	int	ret_status;

	ret_status = 0;
	close(fd[0]);
	signal(SIGINT, SIG_DFL);
	execve(cmd->argv[0], cmd->argv, msh->env);
	ret_status = throw_err(cmd->argv[0], errno);
	write(fd[1], &ret_status, sizeof(int));
	free_and_exit(msh, 0);
}

static int	return_status(int ret_status, int status)
{
	int	ret;

	ret = 0;
	if (ret_status)
		ret = ret_status;
	else if (WEXITSTATUS(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			ret = 130;
		else if (WTERMSIG(status) == 3)
			ret = 131;
	}
	return (ret);
}

int	msh_execve(t_shell *msh, t_cmd *cmd)
{
	pid_t	pid;
	char	*cmd_path;
	int		status;
	int		ret_status;
	int		fd[2];

	cmd_path = get_cmd_path(msh, cmd);
	if (!cmd_path)
		return (cmd->return_value);
	free(cmd->argv[0]);
	cmd->argv[0] = cmd_path;
	ret_status = 0;
	if (pipe(fd))
		ft_putendl(strerror(errno));
	signal(SIGQUIT, SIG_DFL);
	pid = fork();
	if (pid == 0)
		exec_cmd(msh, cmd, fd);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED);
	if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
		printf("Quit\n");
	else if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
		printf("\n");
	close(fd[1]);
	read(fd[0], &ret_status, sizeof(int));
	cmd->return_value = return_status(ret_status, status);
	close(fd[0]);
	return (cmd->return_value);
}
