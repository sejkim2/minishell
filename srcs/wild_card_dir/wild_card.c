/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:44:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/20 16:48:07 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	num_of_file_in_current_directory(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				num_of_file;

	dir = opendir(".");
	if (!dir)
	{
		perror("error\n");
		exit(1);
	}
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

static	char	**make_string_table(s_str_info *str_info, \
int *bit_mask, int count_of_file)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	char			**string_table;

	dir = opendir(".");
	if (!dir)
	{
		perror("error\n");
		exit(1);
	}
	i = 0;
	string_table = malloc(sizeof(char **) * (count_of_file + 1));
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
	return (string_table);
}

char	**get_file_by_wild_card(s_str_info *str_info)
{
	int	count_of_file;
	int	*bit_mask;

	bit_mask = malloc(sizeof(int) * num_of_file_in_current_directory());
	if (!bit_mask)
		malloc_error();
	count_of_file = check_wild_card_pattern(str_info, bit_mask);
	return (make_string_table(str_info, bit_mask, count_of_file));
}
