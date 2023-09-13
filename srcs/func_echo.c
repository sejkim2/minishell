/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:36:27 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/13 20:01:01 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	받은 인자를 문자열로 출력함.
	인자가 다수라면, 각 인자에 공백을 삽입하여 붙여 출력함.
	-n 옵션은 줄바꿈을 붙이지 않음. 따라서 프롬프트가 출력문에 바로 붙어서 들어오게 됨. 
*/

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
	int		idx;
	int		plen;

	if (!*argv)
		return ;
	plen = 0;
	idx = 2;
	while (idx < argc)
	{
		plen += printf("%s", argv[idx]);
		if (idx < argc - 1)
			plen += printf(" ");
		idx++;
	}
	return ;
}

static void	echo_opt(int argc, char **argv)
{
	int		i;
	int		j;

	i = 2;
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
				return (echo_opt_print(argc - i + 2, argv + i - 2));
		}
		i++;
	}
	return (echo_opt_print(argc - i + 2, argv + i - 2));
}

int	main(int argc, char **argv)
{
	if (argc < 2 || strcmp(argv[1], "echo"))
		return (printf("error\n"));
	argv = change_env(argv);
	if (!argv[2] || argv[2][0] != '-')
		echo_no_opt_print(argc, argv);
	else
		echo_opt(argc, argv);
}
