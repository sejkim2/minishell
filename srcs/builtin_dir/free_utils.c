/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:58:29 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 20:09:29 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2str(char *s1, char *s2)
{
	free_str(s1);
	free_str(s2);
}

void	free_4str(char *s1, char *s2, char *s3, char *s4)
{
	free_str(s1);
	free_str(s2);
	free_str(s3);
	free_str(s4);
}

void	free_str(char *str)
{
	if (!str)
		return ;
	else
	{
		free(str);
		str = NULL;
	}
}

void	free_arr(char **arr)
{
	int		idx;

	if (!arr)
		return ;
	idx = 0;
	while (arr[idx])
	{
		free(arr[idx]);
		arr[idx] = NULL;
		idx++;
	}
	free(arr);
	arr = NULL;
}

void	check_malloc_fail(char *buff)
{
	if (!buff)
		malloc_error();
}
