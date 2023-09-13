/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:13:10 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/13 12:42:19 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	인자가 하나일 때: 숫자는 long의 범위 내에 존재해야 함. 인자를 unsigned char형으로
					error코드로 전달하고 종료.
		*	숫자가 아닌 문자거나 long범위 내를 벗어난 수 라면
			bash: exit: "첫 입력string": numeric argument required
			출력문이 발생하고 bash가 종료됨. error코드는 255로 고정
			$?에서 확인할 수 있음.
	인자가 두 개 이상일 때:
		첫 번째 인자가 숫자: bash: exit: too many arguments
						출력문이 발생하고 bash가 종료되지 않음 error코드는 1
		첫 번째 인자가 문자: bash: exit: "첫 입력string": numeric argument required
						출력문이 발생하고 bash가 종료됨. error코드는 255로 고정
	flag는 에러문을 출력할지 말지 판별하는 플래그
*/
void	init_val(long long *n, int *sign, int *flag)
{
	*n = 0;
	*sign = 1;
	*flag = 0;
}

char	*skip_space_get_sign(char *str, int *sign)
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

unsigned char	ft_atol(char *str, int *flag)
{
	long long	n;
	int			sign;

	init_val(&n, &sign, flag);
	str = skip_space_get_sign(str, &sign);
	if (!*str)
	{
		*flag = 1;
		return (255);
	}
	while ('0' <= *str && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		if (n * sign > LONG_MAX || n * sign < LONG_MIN)
			*flag = 1;
		str++;
	}
	while (*str == 32)
		str++;
	if (*str)
	{
		*flag = 1;
		return (255);
	}
	return (n * sign);
}

int	main(int argc, char **argv)
{
	unsigned char	error_code;
	int				flag;

	if (argc == 1 || strcmp(argv[1], "exit"))
		return (printf("error\n"));
	if (argc == 2)
	{
		printf("exit\n");
		exit(0);
	}
	error_code = ft_atol(argv[2], &flag);
	if (argc == 3)
	{
		printf("exit\n");
		if (flag == 1)
			printf("minishell: exit: %s: numeric argument required\n", argv[2]);
	}
	if (argc > 3)
	{
		printf("exit\n");
		if (flag == 1)
			printf("minishell: exit: %s: numeric argument required\n", argv[2]);
		else
			printf("minishell: exit: too many arguments\n");
	}
	exit(error_code);
}
