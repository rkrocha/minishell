
#include "../includes/minishell.h"

int	main(int argc, const char **argv)
{
	int fd;

	fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		printf("%d NOPE\n", fd);
		return 1;
	}
	write(fd, "HELLO!\n", 7);
	close(fd);
	return (0);
}