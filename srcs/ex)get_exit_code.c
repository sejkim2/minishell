#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t c;
	int	status;

	c = fork();
	if (c == 0)
	{
		exit(13);
		execve("ls", argv, envp);
	}
	else
	{
		waitpid(c, &status, 0);
		char *input = readline("input> ");
		if (!strcmp(input, "$?"))
			printf("%d\n", WEXITSTATUS(status));
	}
	return (0);
}