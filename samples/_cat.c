
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

void	cmd_before_pipe(char **argv, char **envp, int *fildes)
{
	int	fd_file;
	char	buffer[256];

	printf("Abrindo o arquivo no processo filho...\n");
	fd_file = open(argv[1], O_RDONLY); // se fechar o fd de leitura antes do open, o open assume o fd 3
	if (fd_file < 0)
		printf("error\n");
	close(fildes[0]); // fecha o fd de leitura
	// dup2(fildes[1], fd_file); // se usar o dup2, quando o processo filho fechar, o fildes[1] tambem fecha e o processo pai perde a referencia
	read(fd_file, buffer, 256);
	write(fildes[1], buffer, 15);
}

void	cmd_after_pipe(char **argv, char **envp, int *fildes)
{
	char	buffer[256];

	close(fildes[1]); // fecha o fd de escrita
	printf("Printando o conteúdo no processo pai...\n");
	read(fildes[0], buffer, 256);
	printf("%s\n", buffer);
}

int main(int argc, char **argv, char **envp)
{
	int		fildes[2];
	int		status;
	pid_t	pid;

	// Cria um pipe e gera dois file descriptors (fildes[0] e fildes[1]) que são usados para os fins de leitura e escrita do pipe:
	status = pipe(fildes); // retorna 0 OK, -1 erro
	if (status == -1)
		printf("error\n");

	pid = fork();
	if (pid == 0)
		cmd_before_pipe(argv, envp, fildes);
	else
	{
		waitpid(pid, NULL, WUNTRACED); // sem o wait, o processo pai se executa ao receber os primeiros dados, descartando o que vier em seguida
		cmd_after_pipe(argv, envp, fildes);
	}

	close(fildes[0]);
	close(fildes[1]);
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
