/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:27:02 by dpiza             #+#    #+#             */
/*   Updated: 2022/01/07 14:15:42 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*alloc_cwd(void)
{
	char	*buffer;
	int		size;

	size = 256;
	buffer = malloc(size * sizeof(char));
	while(!getcwd(buffer, size))
	{
		size += 256;
		free(buffer);
		buffer = malloc(size * sizeof(char));
	}
	return (buffer);
}

static void	update_env_pwd(t_shell *minishell)
{
	t_cmd	*update_pwd;
	char	*old_pwd_var;
	char	*current_pwd;

	current_pwd = alloc_cwd();
	old_pwd_var = get_env(minishell, "PWD");
	update_pwd = malloc(sizeof(t_cmd));
	ft_bzero(update_pwd, sizeof(t_cmd));
	update_pwd->argv = malloc(4 * sizeof(char *));
	update_pwd->argv[0] = ft_strdup("export");
	update_pwd->argv[1] = ft_strjoin("PWD=", current_pwd);
	update_pwd->argv[2] = ft_strjoin("OLDPWD=", old_pwd_var);
	update_pwd->argv[3] = NULL;
	msh_export(minishell, update_pwd);
	free(minishell->pwd);
	minishell->pwd = current_pwd;
	free(old_pwd_var);
	del_cmd(update_pwd);
}

static int	cd_throw_err(int err, char *destiny, int err_no)
{
	if (err == 1)
		ft_putendl("minishell: cd: too many arguments");
	else
	{
		ft_putstr("minishell: cd: ");
		ft_putstr(destiny);
		ft_putstr(": ");
		ft_putendl(strerror(err_no));
	}
	return (1);
}

int	msh_cd(t_shell *minishell, t_cmd *cmd)
{
	char	*destiny;

	if (cmd->argc > 2)
	{
		cmd->return_value = cd_throw_err(1, NULL, 0);
		return (cmd->return_value);
	}
	if (!cmd->argv[1])
		destiny = get_env(minishell, "HOME");
	else if (ft_strncmp(cmd->argv[1], "-", 2) == 0)
		destiny = get_env(minishell, "OLDPWD");
	else
		destiny = ft_strdup(cmd->argv[1]);
	if (chdir(destiny))
		cmd->return_value = cd_throw_err(0, destiny, errno);
	else
		update_env_pwd(minishell);
	free(destiny);
	return (cmd->return_value);
}
