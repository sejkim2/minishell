/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:27:46 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/14 20:04:04 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_2str(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

void	make_str(int i, int j, char **av, char **str)
{
	str[0] = ft_substr(av[i], 0, j - 1);
	str[1] = ft_substr(av[i], j + 1, ft_strlen(av[i] - ft_strlen(str[0]) - 1));
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
	while (str_arr[cnt])
		cnt++;
	return (cnt);
}
