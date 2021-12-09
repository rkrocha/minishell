/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:48:57 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/09 14:08:11 by dpiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	int		status;
	pid_t	pid;

	pid = fork(); // fork retorna um pid para o processo filho, o programa pai continua no else
	if (pid == 0)
	{
		ret = execve(argv[1], argv + 1, envp); // o execve não procura o executável, então o argumento deve conter o caminho
		// if (ret < 0)
		printf("Retorno: %i\n", ret); // execve retorna -1 quando não consegue executar o programa
		printf("%i, %s\n", errno, strerror(errno));
		exit (0);
	}
	else
		waitpid(pid, &status, WUNTRACED); // espera o processo filho encerrar
	return (0);
}