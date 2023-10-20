/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wild_card_pattern.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:24:58 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/20 16:46:03 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	wild_card_type_is_quote(char *str, char **file_name)
{
	*file_name = ft_strnstr(*file_name, str, ft_strlen(*file_name));
	if (*file_name == 0)
		return (0);
	else
	{
		while (*str == **file_name)
		{
			str++;
			(*file_name)++;
		}
		return (1);
	}
}

static	int	check_is_right_wild_card_pattern(char *file_name, \
s_str_info *str_info)
{
	int	i;

	i = 0;
	while (str_info[i].str_type != NUL)
	{
		if (str_info[i].str_type == STRING)
		{
			if (wild_card_type_is_string(str_info[i].str, &file_name) == 0)
				return (0);
		}
		else
		{	
			if (wild_card_type_is_quote(str_info[i].str, &file_name) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_wild_card_pattern(s_str_info *str_info, int *bit_mask)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count_of_file;

	dir = opendir(".");
	count_of_file = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (check_is_right_wild_card_pattern(entry->d_name, str_info))
		{
			*bit_mask = 1;
			count_of_file++;
		}
		else
			*bit_mask = 0;
		bit_mask++;
	}
	closedir(dir);
	return (count_of_file);
}
