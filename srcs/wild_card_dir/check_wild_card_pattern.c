/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wild_card_pattern.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:24:58 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/24 16:38:45 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	check_wild_card(s_str_info *str_info, char *file_name, \
int **bit_mask, int *count_of_file)
{
	if (check_is_right_wild_card_pattern(str_info[0].str, \
	file_name, str_info, 0))
	{
		**bit_mask = 1;
		(*count_of_file)++;
	}
	else
		**bit_mask = 0;
	(*bit_mask)++;
}

int	check_wild_card_pattern(s_str_info *str_info, int *bit_mask)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count_of_file;
	int				hidden_file_flag;

	dir = opendir(".");
	count_of_file = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_name[0] == '.' && str_info[0].str[0] != '.')
		{
			*bit_mask = 0;
			bit_mask++;
			continue ;
		}
		check_wild_card(str_info, entry->d_name, &bit_mask, &count_of_file);
	}
	*bit_mask = -1;
	closedir(dir);
	return (count_of_file);
}
