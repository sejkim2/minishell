/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:44:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/28 15:19:35 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	num_of_file_in_current_directory(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				num_of_file;

	dir = run_opendir();
	num_of_file = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		num_of_file++;
	}
	closedir(dir);
	return (num_of_file);
}

static	char	**make_string_table(int *bit_mask, int count_of_file)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	char			**string_table;
	int				*del_bit;

	dir = run_opendir();
	i = 0;
	string_table = malloc(sizeof(char **) * (count_of_file + 1));
	del_bit = bit_mask;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (*bit_mask == 1)
			string_table[i++] = ft_strdup(entry->d_name);
		bit_mask++;
	}
	string_table[i] = 0;
	closedir(dir);
	free(del_bit);
	return (string_table);
}

static	int	check_is_exist_wild_card(t_str_info	*str_info)
{
	int	i;

	i = 0;
	while (str_info[i].str_type != NUL)
	{
		if (str_info[i].str_type == STRING)
		{
			if (ft_strchr(str_info[i].str, '*') != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

static	int	check_is_exist_bit_mask(int *bit_mask)
{
	int	i;

	i = 0;
	while (bit_mask[i] != -1)
	{
		if (bit_mask[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

char	**get_file_by_wild_card(t_str_info	*str_info)
{
	int	count_of_file;
	int	*bit_mask;

	if (check_is_exist_wild_card(str_info) == 0)
		return (0);
	bit_mask = malloc(sizeof(int) * num_of_file_in_current_directory() + 1);
	if (!bit_mask)
		malloc_error();
	count_of_file = check_wild_card_pattern(str_info, bit_mask);
	if (check_is_exist_bit_mask(bit_mask) == 0)
	{
		free(bit_mask);
		return (0);
	}
	return (make_string_table(bit_mask, count_of_file));
}
