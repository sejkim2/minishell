/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:36:27 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/12 17:36:43 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	echo_no_opt_print(int argc, char **argv)
{
	int		idx;

	if (!argv[2])
	{
		printf("\n");
		return ;
	}
	idx = 2;
	while (idx < argc)
	{
		printf("%s", argv[idx]);
		if (idx < argc - 1)
			printf(" ");
		idx++;
	}
	printf("\n");
	return ;
}

static void	echo_opt_print(int argc, char **argv)
{
	if (!*argv)
		return ;
}

static void	echo_opt(int argc, char **argv)
{
	int		i;
	int		j;

	i = 2;
	while (*argv[i] == '-')
	{
		j = 1;
		while (argv[i][j] == '\n')
		{
			j++;
		}
		i++;
	}
	echo_opt_print(argc, argv);
}

int	main(int argc, char **argv)
{
	if (argc < 2 || strcmp(argv[1], "echo"))
		return (printf("error\n"));
	if (!argv[2] || argv[2][0] != '-')
		echo_no_opt_print(argc, argv);
	else
		echo_opt(argc, argv);
}
