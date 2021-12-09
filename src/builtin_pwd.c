/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:55:15 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/09 10:50:58 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_shell *minishell, t_cmd *cmd)
{
	char	*pwd;

	pwd = minishell->pwd;
	ft_putendl(pwd);
	cmd->return_value = 0;
	return (cmd->return_value);
}
