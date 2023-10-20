/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:27:46 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/20 17:37:36 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_strings(int *i, char **string, char **str)
{
	int		ldx;

	ldx = *i;
	str[0] = ft_substr(*string, 0, *i);
	if (!str[0])
		exit(0);
	while ((*string)[ldx + 1] && (*string)[ldx + 1] != '$' \
	&& (*string)[ldx + 1] != '\'' && (*string)[ldx + 1] != ' ')
		ldx++;
	str[1] = ft_substr(*string, *i, (ldx + 1) - *i);
	if (!str[1])
		exit(0);
	str[2] = ft_strdup("\0");
	if (!str[2])
		exit(0);
	if ((*string)[ldx + 1])
	{
		free(str[2]);
		str[2] = ft_substr(*string, ldx + 1, ft_strlen(*string) - ldx);
		if (!str[2])
			exit(0);
	}
}

void	matrix_cpy(char **src, char **dst)
{
	int		idx;

	idx = 0;
	while (src[idx])
	{
		dst[idx] = src[idx];
		idx++;
	}
}

void	sort_ascii(char **envp, int cnt)
{
	char	*a;
	char	*b;
	int		i;
	int		j;

	while (cnt--)
	{
		i = 0;
		while (envp[i] && envp[i + 1])
		{
			j = 0;
			while (envp[i][j] == envp[i + 1][j])
				j++;
			if (envp[i][j] > envp[i + 1][j])
			{
				a = envp[i];
				b = envp[i + 1];
				envp[i] = b;
				envp[i + 1] = a;
			}
			i++;
		}
	}
}

int	cnt_line(char **str_arr)
{
	int		cnt;

	cnt = 0;
	if (!str_arr)
		return (0);
	while (str_arr[cnt])
		cnt++;
	return (cnt);
}

void	ft_stderror_print(char *cmd, char *argv, char *err_string)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 3);
	if (argv)
	{
		if (!ft_strncmp(cmd, "export", 6))
			write(2, "`", 2);
		write(2, argv, ft_strlen(argv));
		if (!ft_strncmp(cmd, "export", 6))
			write(2, "\'", 2);
		write(2, ": ", 3);
	}
	write(2, err_string, ft_strlen(err_string));
	write(2, "\n", 1);
	g_exit_status = 1;
}
