/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:13:10 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 15:40:30 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	인자가 하나일 때: 숫자는 long의 범위 내에 존재해야 함. 인자를 unsigned char형으로
					error코드로 전달하고 종료.
		*	숫자가 아닌 문자거나 long범위 내를 벗어난 수 라면,
			bash: exit: "첫 입력string": numeric argument required
			출력문이 발생하고 bash가 종료됨. error코드는 255로 고정.
			$?에서 확인할 수 있음.
	인자가 두 개 이상일 때:
		첫 번째 인자가 숫자: bash: exit: too many arguments
						출력문이 발생하고 <bash가 종료되지 않음.> error코드는 1.
		첫 번째 인자가 문자: bash: exit: "첫 입력string": numeric argument required
						출력문이 발생하고 <bash가 종료됨.> error코드는 255로 고정.
	flag는 어떤 에러문을 출력할지 말지 판별하는 플래그.
*/
static char	*skip_space_get_sign(char *str, int *sign)
{
	while (*str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			(*sign) *= -1;
		str++;
	}
	return (str);
}

static void	init_val(t_ull *n, int *sign, int *cnt, int *flag)
{
	*n = 0;
	*sign = 1;
	*cnt = 0;
	*flag = 0;
}

static unsigned char	ft_atol(char *str, int *flag)
{
	t_ull	n;
	int		s;
	int		c;

	init_val(&n, &s, &c, flag);
	str = skip_space_get_sign(str, &s);
	if (!*str)
		*flag = 1;
	while ('0' <= *str && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		str++;
		c++;
	}
	while (*str == 32)
		str++;
	if ((n > (t_ull)LONG_MAX && s == 1) || (n > (t_ull)LONG_MAX + 1 && s == -1) \
	|| *str || c > 19)
		*flag = 1;
	if (*flag == 1)
		return (255);
	return (n * s);
}

static void	exit_fork(void)
{
	pid_t	child;

	child = fork();
	if (child == 0)
		exit(1);
	exit_status = 1;
}

void	builtin_exit(char **cmd_argv)
{
	unsigned char	error_code;
	int				flag;
	int				cmd_argc;

	cmd_argc = cnt_line(cmd_argv);
	write(2, "exit\n", 6);
	if (!cmd_argc)
		exit(0);
	error_code = ft_atol(*cmd_argv, &flag);
	if (cmd_argc)
	{
		if (flag == 1)
		{
			ft_stderror_print("exit", *cmd_argv, "numeric argument required");
			exit(255);
		}
		else if (cmd_argc > 2 && flag == 0)
		{
			ft_stderror_print("exit", NULL, "too many arguments");
			return (exit_fork());
		}
	}
	exit(error_code);
}
