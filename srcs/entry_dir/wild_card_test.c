/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:44:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/18 15:09:59 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_first_cursor_character(char *str, char ch)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == ch)
			return (index);
		index++;
	}
	return (index);
}

//string
static	int	func1(char *str, char **file_name)
{
	int		cur_wild_card;
	char	*sub_str;
	int		i;

	while (*str)
	{
		if (*str == '*')
		{
			while (*str == '*')
				str++;
			if (!*str)
				return (1);
			cur_wild_card = get_first_cursor_character(str, '*');
			sub_str = ft_substr(str, 0, cur_wild_card);
			if (!sub_str)
				malloc_error();
			*file_name = ft_strnstr(*file_name, sub_str, ft_strlen(*file_name));
			free(sub_str);
			if (*file_name == 0)
				return (0);
			i = 0;
			while (i < cur_wild_card)
			{
				str++;
				(*file_name)++;
				i++;
			}
		}
		else
		{
			if (*str != **file_name)
				return (0);
			else
			{
				str++;
				(*file_name)++;
			}
		}
	}
	if (**file_name)
		return (0);
	return (1);
}

//quote
static	int	func2(char *str, char **file_name)
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

static	int	check_is_right_wild_card_pattern(char *file_name, s_str_info *str_info)
{
	int	i;
	int j;

	i = 0;
	while (str_info[i].str_type != NUL)
	{
		if (str_info[i].str_type == STRING)
		{
			if (func1(str_info[i].str, &file_name) == 0)
				return (0);
		}
		else
		{	if (func2(str_info[i].str, &file_name) == 0)
				return (0);
		}
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
	char 			**string_table;
	int				siz;

	// int tmp;
	// tmp = 0;
	// while (str_info[tmp].str_type != NUL)
	// {
	// 	printf("%s\n", str_info[tmp].str);
	// 	tmp++;
	// }
	count_of_file = 0;
	dir = opendir(".");
	if (!dir)
	{
		perror("error\n");
		exit(1);
	}
	siz = num_of_file_in_current_directory(dir);
	bit_mask = malloc(sizeof(int) * siz);
	if (!bit_mask)
		malloc_error();
	closedir(dir);
	dir = opendir(".");
	index = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (check_is_right_wild_card_pattern(entry->d_name, str_info))
		{
			bit_mask[index] = 1;
			count_of_file++;
		}
		else
			bit_mask[index] = 0;
		index++;
	}
	closedir(dir);

	dir = opendir(".");
	if (!dir)
	{
		perror("error\n");
		exit(1);
	}
	int j = 0;
	index = 0;
	string_table = malloc(sizeof(char **) * (count_of_file + 1));
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (bit_mask[index] == 1)
			string_table[j++] = ft_strdup(entry->d_name);
		index++;
	}
	string_table[j] = 0;
	closedir(dir);
	return (string_table);
}