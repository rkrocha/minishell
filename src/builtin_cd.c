/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:27:02 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/08 14:24:51 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(t_shell *minishell, t_cmd *cmd)
{
	// char	*full_path;

	// full_path = ft_calloc(128 * sizeof(char));
	// getcwd(full_path, sizeof(full_path));
	// full_path = ft_strjoin_free(&full_path, "/");
	// full_path = ft_strjoin_free(&full_path, cmd->cmd_v[1]);
	// if (access(full_path, F_OK))
	// 	cmd->return_value = chdir(cmd->cmd_v[1]);
	// else if (!*cmd->cmd_v[1])
	// 	cmd->return_value = chdir(get_env("$HOME"));
	// else
	// {
	// 	ft_putstr("msh: cd: ")
	// 	ft_putstr(cmd->cmd_v[1]);
	// 	ft_putendl("No such file or directory");
	// 	cmd->return_value = 1;
	// }
	(void)minishell;
	cmd->return_value = chdir(cmd->cmd_v[1]);
	if (cmd->return_value)
		perror(strerror(cmd->return_value));
	return (cmd->return_value);
}

int	msh_pwd(t_shell *minishell, t_cmd *cmd)
{
	char	buffer[128];

	(void)minishell;
	(void)cmd;
	if (!getcwd(buffer, 128))
		ft_putendl("NULL");
	ft_putendl(buffer);
	return (0);
}
