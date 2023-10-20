/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:13:10 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/18 16:47:36 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_exit_status = 1;
}

void	builtin_exit(char **cmd_argv)
{
	int				flag;
	int				cmd_argc;

	g_exit_status = 0;
	cmd_argc = cnt_line(cmd_argv);
	write(2, "exit\n", 6);
	if (!cmd_argc)
		exit(g_exit_status);
	g_exit_status = ft_atol(*cmd_argv, &flag);
	if (flag == 1)
	{
		ft_stderror_print("exit", *cmd_argv, "numeric argument required");
		exit(g_exit_status);
	}
	else if (cmd_argc > 1 && flag == 0)
	{
		ft_stderror_print("exit", NULL, "too many arguments");
		return (exit_fork());
	}
	exit(g_exit_status);
}
