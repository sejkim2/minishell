/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:44:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/17 20:34:58 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//string
static	int	func1(char *str, char **file_name)
{
	while (*str)
	{
		if (*str == '*')
		{
			while (*str == '*')
				str++;
			if (!*str)
				return (1);
			if (ft_strnstr(*file_name, *str, ft_strlen(*file_name)) == 0)
				return (0);
			while (**file_name != *str)
				(*file_name)++;
		}
		else
			if (*str != **file_name)
				return (0);
		str++;
		(*file_name)++;
	}
	return (1);
}

//quote
static	int	func2(char *str, char *file_name)
{
	while (*str)
	{
		if (*str != **file_name)
			return (0);
		str++;
		(*file_name)++;
	}
	return (1);
}

static	int	check_is_right_wild_card_pattern(char *file_name, s_str_info *str_info)
{
	int	i;
	int j;

	i = 0;
	while (str_info[i].str_type != NUL)
	{
		if (str_info[i].str_type == STRING)
			if (!func1(str_info[i].str, &file_name))
				return (0);
		/*single or double qoute*/
		else
			if (!func2(str_info[i].str, &file_name))
				return (0);
		i++;
	}
	return (1);
}

static	int	num_of_file_in_current_directory(DIR *dir)
{
	struct dirent	*entry;
	int				num_of_file;

	num_of_file = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		num_of_file++;
	}
	return (num_of_file);
}

char	**get_file_by_wild_card(s_str_info	*str_info)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count_of_file;
	int				*bit_mask;
	int				index;

	count_of_file = 0;
	dir = opendir(".");
	if (!dir)
	{
		perror("error\n");
		exit(1);
	}
	bit_mask = malloc(sizeof(int) * num_of_file_in_current_directory(dir));
	if (!bit_mask)
		malloc_error();
	index = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (check_is_right_wild_card_pattern(entry->d_name, str_info))
		{
			bit_mask[index++] = 1;
			count_of_file++;
		}
		else
			bit_mask[index++] = 0;
	}
	closedir(dir);
	return (0);
}