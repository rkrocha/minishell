/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:44:59 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/20 13:18:57 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_input(void)
{
	struct stat	info;

	fstat(0, &info);
	if (info.st_mode != 8592)
		return (TRUE);
	return (FALSE);
}
