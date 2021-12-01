/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:51:18 by dpiza             #+#    #+#             */
/*   Updated: 2021/11/30 21:31:32 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <bsd/bsd.h>

void	check_file_access(const char *folder, const char *ent_name, int *ent_access)
{
	char	full_path[128];

	bzero(full_path, 128);
	strcat(full_path, folder);
	strcat(full_path, "/");
	strcat(full_path, ent_name);
	// printf("%s", full_path);
	ent_access[0] = access(full_path, R_OK); // identifica a permissão de leitura
	ent_access[1] = access(full_path, W_OK);
	ent_access[2] = access(full_path, X_OK);
	ent_access[3] = access(full_path, F_OK);
}

void	print_access(int *ent_access, int d_type, char *d_name)
{
	char	r;
	char	w;
	char	x;

	if (strnstr(d_name, "..", 3) || strnstr(d_name, ".", 2) || ent_access[3])
		return ;
	r = '-';
	w = '-';
	x = '-';
	if (ent_access[0] == 0)
		r = 'r';
	if (ent_access[1] == 0)
		w = 'w';
	if (ent_access[2] == 0)
		x = 'x';
	printf("%c%c%c", r, w, x);
	printf(" %3i\t%s\n", d_type, d_name);
}

int	main(int c, char **v)
{
	struct dirent	*ret;
	DIR				*diretorio;
	int				ent_access[4];

	if (c < 2)
		return (1);
	diretorio = opendir(v[1]); // retorna um ponteiro pro primeiro item da pasta
	if (!diretorio)
		return (1);
	while(ret = readdir(diretorio)) // itera cada item da pasta
	{
		if (ret == NULL)
			break ;
		check_file_access(v[1], ret->d_name, ent_access); // verifica a permissão de um item da pasta
		print_access(ent_access, ret->d_type, ret->d_name); // printa as permissões
	}
	closedir(diretorio); // fecha a pasta pra não dar leak
	return (0);
}

/* compilar usando -lbsd */