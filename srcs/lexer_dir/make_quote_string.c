/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_quote_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:04 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/24 17:18:21 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_str_info	*make_and_init_str_info(char *cmd_line, int start, int end)
{
	int			len_string;
	t_str_info	*str_info;

	len_string = count_quote_string(cmd_line, start, end);
	str_info = malloc(sizeof(t_str_info) * (len_string + 1));
	if (str_info == 0)
		malloc_error();
	str_info[len_string].str = 0;
	str_info[len_string].str_len = 0;
	str_info[len_string].str_type = NUL;
	return (str_info);
}

static	void	set_single_quote(char *cmd_line, \
int *start, int end, t_str_info *str_info)
{
	int	i;

	i = *start + 1;
	single_close_quote(cmd_line, start, end);
	str_info->str = ft_substr(cmd_line, i, *start - i - 1);
	str_info->str_len = ft_strlen(str_info->str);
	str_info->str_type = SINGLE_QUOTE;
}

static	void	set_double_quote(char *cmd_line, \
int *start, int end, t_str_info *str_info)
{
	int	i;

	i = *start + 1;
	double_close_quote(cmd_line, start, end);
	str_info->str = ft_substr(cmd_line, i, *start - i - 1);
	str_info->str_len = ft_strlen(str_info->str);
	str_info->str_type = DOUBLE_QUOTE;
}

static	void	set_normal_string(char *cmd_line, \
int *start, int end, t_str_info *str_info)
{
	int	i;

	i = *start;
	normal_string(cmd_line, start, end);
	str_info->str = ft_substr(cmd_line, i, *start - i);
	str_info->str_len = ft_strlen(str_info->str);
	str_info->str_type = STRING;
}

t_str_info	*make_quote_string(char *cmd_line, int start, int end)
{
	int			len_string;
	t_str_info	*str_info;
	t_str_info	*info_address;

	str_info = make_and_init_str_info(cmd_line, start, end);
	info_address = str_info;
	while (start < end)
	{
		if (check_is_single_quote(cmd_line[start]) \
		&& check_is_close_quote(cmd_line, start, '\''))
			set_single_quote(cmd_line, &start, end, str_info);
		else if (check_is_double_quote(cmd_line[start]) \
		&& check_is_close_quote(cmd_line, start, '\"'))
			set_double_quote(cmd_line, &start, end, str_info);
		else
			set_normal_string(cmd_line, &start, end, str_info);
		str_info++;
	}
	return (info_address);
}
