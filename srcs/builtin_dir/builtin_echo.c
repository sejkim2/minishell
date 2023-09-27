/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:36:27 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/27 15:39:15 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	받은 인자를 문자열로 출력함.
	인자가 다수라면, 각 인자에 공백을 삽입하여 붙여 출력함.
	-n 옵션은 줄바꿈을 붙이지 않음. 따라서 프롬프트가 출력문에 바로 붙어서 들어오게 됨. 
*/

static void	echo_no_opt_print(int argc, char **argv)
{
	int		idx;

	if (!*argv)
	{
		printf("\n");
		return ;
	}
	idx = 0;
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
	int		idx;

	idx = 0;
	while (idx < argc)
	{
		printf("%s", argv[idx]);
		if (idx < argc - 1)
			printf(" ");
		idx++;
	}
	return ;
}

static int	echo_opt_flag(char *argv)
{
	int		idx;

	idx = 1;
	while (argv[idx] && argv[idx] == 'n')
		idx++;
	if (argv[idx] != '\0')
		return (0);
	return (1);
}

static void	echo_opt(int argc, char **argv)
{
	int		i;
	int		j;

	if (echo_opt_flag(*argv))
	{
		i = 0;
		while (argv[i] && *argv[i] == '-')
		{
			j = 1;
			if (!argv[i][j])
				break ;
			while (argv[i][j])
			{
				if (argv[i][j] == 'n')
					j++;
				else
					return (echo_opt_print(argc - i, argv + i));
			}
			i++;
		}
		return (echo_opt_print(argc - i, argv + i));
	}
	else
		return (echo_no_opt_print(argc, argv));
}

// int	main(int argc, char **argv, char **envp)
// {
// 	if (argc < 2 || strcmp(argv[1], "echo"))
// 		return (printf("error\n"));
// 	argv = change_env(argv, envp);
// 	if (!argv[2] || argv[2][0] != '-' || !argv[2][1])
// 		echo_no_opt_print(argc - 2, argv + 2);
// 	else
// 		echo_opt(argc - 2, argv + 2);
// 	exit(0);
// }
