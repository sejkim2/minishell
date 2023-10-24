/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_right_wild_card_pattern.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:28:32 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/24 17:20:08 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	push_wild_card(char **str, char **file, \
t_str_info *str_info, int *i)
{
	while (**str == '*')
		(*str)++;
	if (**str == '\0')
	{
		*i = *i + 1;
		if (str_info[*i].str_type == NUL)
			return (1);
		*str = str_info[*i].str;
	}
	return (0);
}

static	int	is_case_is_not_wild_card(char **str, char **file, \
t_str_info *str_info, int *i)
{
	if (**str != **file)
		return (0);
	else
	{
		(*str)++;
		(*file)++;
		if (**str == '\0')
		{
			*i = *i + 1;
			if (str_info[*i].str_type == NUL)
				return (-1);
			*str = str_info[*i].str;
		}
	}
	return (1);
}

static int	check_return_value(char ch)
{
	if (ch == '\0')
		return (1);
	else
		return (0);
}

static int	if_case_is_wild_card(char *str, char **file, \
t_str_info *str_info, int i)
{
	char	*tmp;
	int		flag;

	tmp = *file;
	flag = 0;
	while (*tmp)
	{
		if (check_is_right_wild_card_pattern(str, tmp, str_info, i) == 1)
		{
			*file = tmp;
			flag = 1;
			break ;
		}
		tmp++;
	}
	if (flag == 0)
		return (0);
	else
		return (1);
}

int	check_is_right_wild_card_pattern(char *str, char *file, \
t_str_info *str_info, int i)
{
	char	*tmp;
	int		flag;

	while (*str)
	{
		if (str_info[i].str_type == STRING && *str == '*')
		{
			if (push_wild_card(&str, &file, str_info, &i) == 1)
				return (1);
			flag = if_case_is_wild_card(str, &file, str_info, i);
			if (flag == 0)
				return (0);
		}
		else
		{
			flag = is_case_is_not_wild_card(&str, &file, str_info, &i);
			if (flag == -1)
				break ;
			else if (flag == 0)
				return (0);
		}
	}
	return (check_return_value(*file));
}
