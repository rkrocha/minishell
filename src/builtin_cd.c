/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:27:02 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/14 14:23:43 by dpiza            ###   ########.fr       */
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
	update_pwd->argv = malloc(3 * sizeof(char *));
	update_pwd->argv[0] = ft_strdup("export");
	update_pwd->argv[1] = ft_strjoin("PWD=", getcwd(buffer, 128));
	update_pwd->argv[2] = NULL;
	msh_export(minishell, update_pwd);
	update_old_pwd = malloc(sizeof(t_cmd));					// quando o msh_export estiver pronto manda tudo em 1 comando só
	ft_bzero(update_old_pwd, sizeof(t_cmd));
	update_old_pwd->argv = malloc(3 * sizeof(char *));
	update_old_pwd->argv[0] = ft_strdup("export");
	update_old_pwd->argv[1] = ft_strjoin("OLDPWD=", old_pwd_var);
	update_old_pwd->argv[2] = NULL;
	msh_export(minishell, update_old_pwd);
	free(minishell->pwd);
	minishell->pwd = ft_strdup(buffer);
	free(old_pwd_var);
	del_cmd(update_pwd);
	del_cmd(update_old_pwd);
}

int	msh_cd(t_shell *minishell, t_cmd *cmd)
{
	char	*destiny;

	if (!cmd->argv[1])
		destiny = get_env(minishell, "HOME");
	else if (ft_strncmp(cmd->argv[1], "-", 2) == 0)
		destiny = get_env(minishell, "OLDPWD");
	else
		destiny = ft_strdup(cmd->argv[1]);
	if (chdir(destiny))
	{
		ft_putstr("minishell: cd: ");
		ft_putstr(destiny);
		ft_putstr(": ");
		ft_putendl(strerror(errno));
		cmd->return_value = 1;
	}
	else
		update_env_pwd(minishell);
	free(destiny);
	return (cmd->return_value);
}
