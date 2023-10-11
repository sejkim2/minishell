#include "minishell.h"

int	main(void)
{
	pid_t c;
	int	fd[2];
	char	*line;

	pipe(fd);
	c = fork();

	if (c == 0)
	{
		int	infile = open("txt", O_RDONLY, 0644);
		dup2(fd[1], 1);
		dup2(fd[0], 0);
		line = get_next_line(fd[0])
		while ()
	}
}