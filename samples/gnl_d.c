#include "minishell.h"

int main(int argc, char **argv)
{
	char *read;

	while(1)
	{
		read = get_next_line(0);
		if (!read)
		{
			printf("NULO\n");
			return (0);
		}
		if (!ft_strncmp(read, "EOF\n", 4))
		{
			free(read);
			break ;
		}
		printf("%s\n", read);
		free(read);
	}
}
