/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:55:15 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/08 22:52:40 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_shell *minishell, t_cmd *cmd)
{
	char	*pwd;

	pwd = get_env(minishell, "PWD");
	ft_putendl(pwd);
	free (pwd);
	cmd->return_value = 0;
	return (cmd->return_value);
}
