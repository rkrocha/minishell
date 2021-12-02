/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:35:38 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/01 12:59:04 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(int c, char **v, char **e)
{
	int	fd;
	int	ret;
	int	slot;
	char	*name;

	fd = 1;
	ret = isatty(fd); // retorna 1 se o fd for de um terminal, 0 se não for
	name = ttyname(fd); // retorna o nome do terminal identificado pelo fd
	slot = ttyslot(); // if none of the file descriptors 0, 1, or 2 is associated  with a terminal retorna 0 (legado)
	printf("isatty: %i\nttyslot: %i\nttyname: %s\n", ret, slot, name);
}
