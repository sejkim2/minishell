/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_type_is_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:32:34 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/18 16:35:49 by sejkim2          ###   ########.fr       */
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

int	wild_card_type_is_string(char *str, char **file_name)
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