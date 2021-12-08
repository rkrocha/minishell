/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:27:02 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/08 20:57:38 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_pwd(t_shell *minishell)
{
	char	buffer[128];
	t_cmd	*update_pwd;
	t_cmd	*update_old_pwd;
	char	*old_pwd_var;

	old_pwd_var = get_env(minishell, "PWD");
	update_pwd = malloc(sizeof(t_cmd));						// quando o msh_export estiver pronto manda tudo em 1 comando só
	ft_bzero(update_pwd, sizeof(t_cmd));
	update_pwd->cmd_v = malloc(3 * sizeof(char *));
	update_pwd->cmd_v[0] = ft_strdup("export");
	update_pwd->cmd_v[1] = ft_strjoin("PWD=", getcwd(buffer, 128));
	update_pwd->cmd_v[2] = NULL;
	msh_export(minishell, update_pwd);
	update_old_pwd = malloc(sizeof(t_cmd));					// quando o msh_export estiver pronto manda tudo em 1 comando só
	ft_bzero(update_old_pwd, sizeof(t_cmd));
	update_old_pwd->cmd_v = malloc(3 * sizeof(char *));
	update_old_pwd->cmd_v[0] = ft_strdup("export");
	update_old_pwd->cmd_v[1] = ft_strjoin("OLDPWD=", old_pwd_var);
	update_old_pwd->cmd_v[2] = NULL;
	msh_export(minishell, update_old_pwd);
	free(old_pwd_var);
	del_cmd(update_pwd);
	del_cmd(update_old_pwd);
}

static char	*expand_home(t_shell *minishell, char *cmd)
{
	char	*path;
	char	*folder;
	char	*full_path;

	if (ft_strncmp(cmd, "~", 2) == 0)
		return (get_env(minishell, "HOME"));
	path = get_env(minishell, "HOME");
	folder = ft_substr(cmd, 1, ft_strlen(cmd));
	full_path = ft_strjoin_free(&path, folder);
	free (folder);
	return (full_path);
}

int	msh_cd(t_shell *minishell, t_cmd *cmd)
{
	char	*destiny;

	if (ft_strncmp(cmd->cmd_v[1], "~", 1) == 0)
		destiny = expand_home(minishell, cmd->cmd_v[1]);
	else if (ft_strncmp(cmd->cmd_v[1], "-", 2) == 0)
		destiny = get_env(minishell, "OLDPWD");
	else
		destiny = ft_strdup(cmd->cmd_v[1]);
	cmd->return_value = chdir(destiny);
	if (cmd->return_value)
	{
		ft_putstr("minishell: cd: ");
		ft_putstr(destiny);
		ft_putstr(": ");
		ft_putendl(strerror(errno));
	}
	else
		update_env_pwd(minishell);
	free(destiny);
	return (cmd->return_value);
}
