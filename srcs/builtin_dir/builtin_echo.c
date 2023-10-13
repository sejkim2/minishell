/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:36:27 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/13 20:28:54 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	받은 인자를 문자열로 출력함.
	인자가 다수라면, 각 인자에 공백을 삽입하여 붙여 출력함.
	-n 옵션은 줄바꿈을 붙이지 않음. 따라서 프롬프트가 출력문에 바로 붙어서 들어오게 됨. 
*/

static void	echo_no_opt_print(int cmd_argc, char **cmd_argv)
{
	int		idx;

	if (cmd_argc == 0)
	{
		printf("\n");
		return ;
	}
	idx = 0;
	while (idx < cmd_argc)
	{
		printf("%s", cmd_argv[idx]);
		if (idx < cmd_argc - 1)
			printf(" ");
		idx++;
	}
	printf("\n");
	return ;
}

static void	echo_opt_print(int cmd_argc, char **cmd_argv)
{
	int		idx;

	idx = 0;
	while (idx < cmd_argc)
	{
		printf("%s", cmd_argv[idx]);
		if (idx < cmd_argc - 1)
			printf(" ");
		idx++;
	}
	return ;
}

static int	echo_opt_flag(char *str)
{
	int		idx;

	idx = 1;
	while (str[idx] && str[idx] == 'n')
		idx++;
	if (str[idx] != '\0')
		return (0);
	return (1);
}

static void	echo_opt(int cmd_argc, char **cmd_argv)
{
	int		i;
	int		j;

	if (echo_opt_flag(*cmd_argv)) // 첫 인자에서 일단, opt가 적용되는지를 확인.
	{
		i = 1;
		while (cmd_argv[i][0] == '-')
		{
			j = 1;
			if (!cmd_argv[i][j])
				break ;
			while (cmd_argv[i][j])
			{
				if (cmd_argv[i][j] == 'n')
					j++;
				else
					return (echo_opt_print(cmd_argc - i, cmd_argv + i));
			}
			i++;
		}
		return (echo_opt_print(cmd_argc - i, cmd_argv + i));
	}
	else
		return (echo_no_opt_print(cmd_argc, cmd_argv));
}

void	builtin_echo(char **cmd_argv, char **env)
{
	int		cmd_argc;

	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc || *cmd_argv[0] != '-' || !*cmd_argv[1]) //인자가 없거나, 첫 인자가 '-'로 시작하지 않거나, 첫 인자가 '-'이기만 하다면 no opt
		echo_no_opt_print(cmd_argc, cmd_argv);
	else
		echo_opt(cmd_argc, cmd_argv);
}
