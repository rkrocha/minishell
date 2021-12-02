/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:52:13 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/01 11:11:33 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int c, char **v, char **e)
{
	char buffer[256];
	
	getcwd(buffer, sizeof(buffer)); // retorna o pwd (antes do cd)
	printf("%s\n", buffer);
	chdir(v[1]);
	getcwd(buffer, sizeof(buffer)); // retorna o pwd
	printf("%s\n", buffer);
	
	return (0);
}
