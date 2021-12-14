/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiza <dpiza@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:48:57 by dpiza             #+#    #+#             */
/*   Updated: 2021/12/13 21:48:10 by dpiza            ###   ########.fr       */
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
	char	buffer[512];
	pid_t	pid;

	i = 0;
	while (argv[++i])
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], 1);
			// close(fd[1]);
			// close(fd[0]);
			execlp(argv[i], argv[i], NULL);
		}
		waitpid(pid, &status, WUNTRACED);
		dup2(fd[0], 0);
		close(fd[1]);
	}
	read(fd[0], buffer, 512);
	printf("Buffer:\n%s", buffer);
	close(fd[0]);
	return (0);
}
