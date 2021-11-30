/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:51:18 by dpiza             #+#    #+#             */
/*   Updated: 2021/11/30 15:02:04 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void	check_file_access(const char *folder, const char *ent_name, int *ent_access)
{
	char	full_path[128];

	bzero(full_path, 128);
	strcat(full_path, folder);
	strcat(full_path, ent_name);
	// printf("%s", full_path);
	ent_access[0] = access(full_path, R_OK); // identifica a permissão de leitura
	ent_access[1] = access(full_path, W_OK);
	ent_access[2] = access(full_path, X_OK);
	ent_access[3] = access(full_path, F_OK);
}

int	main(int c, char **v)
{
	char	*path;
	struct dirent	*ret;
	DIR	*diretorio;
	int		ent_access[4];

	path = getenv("PATH"); // retorna a variável PATH do sistema nativo
	printf("%s\n", path);
	diretorio = opendir(v[1]); // retorna um ponteiro pro primeiro item da pasta
	while(ret = readdir(diretorio)) // itera cada item da pasta
	{
		if (ret == NULL)
			break ;
		check_file_access(v[1], ret->d_name, ent_access); // verifica a permissão de um item da pasta
		printf("R:%i W:%i X:%i F:%i", ent_access[0], ent_access[1],
						ent_access[2], ent_access[3]);
		printf(" %i %s\n", ret->d_type, ret->d_name);
	}
	closedir(diretorio); // fecha a pasta pra não dar leak
	return (0);
}