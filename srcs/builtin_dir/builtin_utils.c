/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:27:46 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/26 17:02:49 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	matrix_cpy(char **dest, char **origin)
{
	int		idx;

	idx = 0;
	while (origin[idx])
	{
		dest[idx] = ft_strdup(origin[idx]);
		idx++;
	}
	dest[idx] = NULL;
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
		if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
			write(2, "`", 2);
		write(2, argv, ft_strlen(argv));
		if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
			write(2, "\'", 2);
		write(2, ": ", 3);
	}
	write(2, err_string, ft_strlen(err_string));
	write(2, "\n", 1);
	g_exit_status = 1;
}
