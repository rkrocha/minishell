#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char		buffer[512];
	struct stat	info;

	while (1)
	{
		printf("\n\nInput:\n");
		fflush(stdout);
		int nread = read(0, buffer, 511);
		buffer[nread] = '\0';
		printf("Output:\n%s_______________________________________\n", buffer);

		fstat(0, &info); // Traz info de um arquivo aberto associado ao fd, nesse caso 0
		printf("fd info - type/mode: %d size: %d\n", info.st_mode, info.st_size);

		if (info.st_mode != 8592)
			break ;
	}

	// Ler input do stdin (função read na linha 10) retorna st_mode = 8592
	// Ler input de heredoc retorna st_mode = 4480
	// Ler input de arquivo retorna st_mode = 33188
	// https://jameshfisher.com/2017/02/24/what-is-mode_t/

	// no minishell.c:, função handle_cmd, primeira linha:
	// 		se st_mode do fd 0 for diferente de 8592, então minishell->end = TRUE
	return (0);
}
