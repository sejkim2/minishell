/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:43:22 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/28 16:48:06 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*malloc_string(char *str)
{
	char	*rstr;

	rstr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!rstr)
		malloc_error();
	return (rstr);
}

static char	*make_new_filename(char *str)
{
	int		i;
	char	*rstr;

	while (access(str, F_OK) == 0)
	{
		i = 0;
		rstr = malloc_string(str);
		ft_memcpy(rstr, str, ft_strlen(str));
		while (i < 10)
		{
			rstr[ft_strlen(str)] = i + '0';
			rstr[ft_strlen(str) + 1] = '\0';
			if (access(rstr, F_OK) == -1)
			{
				free(str);
				return (rstr);
			}
			i++;
		}
		rstr[ft_strlen(str)] = '_';
		free(str);
		str = rstr;
	}
	return (str);
}

char	*generate_temp_filename(char *mode)
{
	char	*str;

	str = ft_strdup(mode);
	if (access(str, F_OK) == -1)
		return (str);
	else
		return (make_new_filename(str));
}
