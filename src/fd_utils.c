/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:44:59 by rkochhan          #+#    #+#             */
/*   Updated: 2021/12/28 14:53:17 by rkochhan         ###   ########.fr       */
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

void	print_from_pipe(int fd)
{
	char	*str;

	while (TRUE)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		ft_putstr(str);
		free(str);
	}
}
