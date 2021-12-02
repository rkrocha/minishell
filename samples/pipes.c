
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
	int		fildes[2];
	int		status;
	pid_t	pid;
	char	buffer[256];

	// Cria um pipe e gera dois file descriptors (fildes[0] e fildes[1]) que são usados para os fins de leitura e escrita do pipe:
	status = pipe(fildes); // retorna 0 OK, -1 erro

	if (status == -1)
		printf("error\n");

	pid = fork();

	if (pid == 0)
	{
		close(fildes[0]); // fecha o fd de leitura
		printf("Escrevendo no FD\n");
		dprintf(fildes[1], "Escrito 1 no filho");
		sleep(1);
		dprintf(fildes[1], "Escrito 2 no filho");
		// cmd_before_pipe(argv, envp, fildes);
	}
	else
	{
		close(fildes[1]); // fecha o fd de escrita
		waitpid(pid, NULL, 0); // sem o wait, o processo pai se executa ao receber os primeiros dados, descartando o que vier em seguida
		read(fildes[0], buffer, 36);
		printf("Lendo no processo pai: %s\n", buffer);
		// cmd_after_pipe(argv, envp, fildes);

	}

	// close(fildes[0]);
	// close(fildes[1]);
	return (0);
}

// fork() This  function  creates  a  new process. The return value is the zero in the child and the process-id number of the child in the parent, or -1 upon error. In the latter case, ERRNO indicates the problem. In the child, PROCINFO["pid"] and PROCINFO["ppid"] are updated to reflect the correct values.

// wait:
// 0      meaning wait for any child process whose process group ID is equal to that of the calling process  at the time of the call to waitpid().

// > 0    meaning wait for the child whose process ID is equal to the value of pid.


// if (cpid == 0) {    /* Child reads from pipe */
//                close(pipefd[1]);          /* Close unused write end */

//                while (read(pipefd[0], &buf, 1) > 0)
//                    write(STDOUT_FILENO, &buf, 1);

//                write(STDOUT_FILENO, "\n", 1);
//                close(pipefd[0]);
//                _exit(EXIT_SUCCESS);

//            } else {            /* Parent writes argv[1] to pipe */
//                close(pipefd[0]);          /* Close unused read end */
//                write(pipefd[1], argv[1], strlen(argv[1]));
//                close(pipefd[1]);          /* Reader will see EOF */
//                wait(NULL);                /* Wait for child */
//                exit(EXIT_SUCCESS);
//            }
