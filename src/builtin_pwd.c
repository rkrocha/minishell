/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:55:15 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/08 15:02:53 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_shell *minishell, t_cmd *cmd)
{
	char	buffer[128];

	(void)minishell;
	if (!getcwd(buffer, 128))
		perror(strerror(errno));
	else
		ft_putendl(buffer);
	cmd->return_value = 0;
	return (cmd->return_value);
}
