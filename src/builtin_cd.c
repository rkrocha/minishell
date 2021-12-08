/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:27:02 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/08 19:36:51 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(t_shell *minishell, t_cmd *cmd)
{
	char	buffer[128];
	t_cmd	*update_pwd;
	t_cmd	*update_old_pwd;
	char	*old_pwd_var;

	cmd->return_value = chdir(cmd->cmd_v[1]);
	if (cmd->return_value)
		perror(strerror(errno));
	old_pwd_var = get_env(minishell, "PWD");
	
	update_pwd = malloc(sizeof(t_cmd));
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
	return (cmd->return_value);
}
