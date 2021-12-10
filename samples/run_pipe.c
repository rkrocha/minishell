/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:48:57 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/10 14:27:49 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		fd[2];
	int		i;
	char	buffer[256];
	pid_t	pid;
	int		open_fd;

	i = 0;
	while (argv[++i])
	{
		pipe(fd);
		open_fd = open("open_fd", O_RDWR, 0666);
		pid = fork(); // fork retorna um pid para o processo filho, o programa pai continua no else
		if (pid == 0)
		{
			write(open_fd, "z\nc\na\n", 6);
			dup2(open_fd, 0);
			close(open_fd);
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execve(argv[i], argv + i, envp);
			exit (0);
		}
		else
		{
			waitpid(pid, &status, WUNTRACED);
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			dup2(open_fd, 1);
			close(open_fd);

			read(0, buffer, 256);
			printf("Buffer: %s", buffer);
			// dup2(1, 0);
			// close(0);
			// close(1);
		}
	}

	return (0);
}
