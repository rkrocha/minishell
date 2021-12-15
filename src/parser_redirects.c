/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:46:34 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/15 14:01:07 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_redirects(char redir_type, t_cmd *cmd)
{
	(void)redir_type;
	(void)cmd;
	return (0);
}

void	cmd_redirects_parser(t_shell *minishell, t_cmd *cmd)
{
	// int	i;

	(void)minishell;
	(void)cmd;
	count_redirects('>', cmd);
}

// <<< redireciona string para input: fora do escopo (erro)
