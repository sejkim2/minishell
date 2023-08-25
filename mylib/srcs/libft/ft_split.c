/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:57:36 by sejkim2           #+#    #+#             */
/*   Updated: 2023/06/08 11:47:45 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	row_size(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
	}
	return (count);
}

int	make_split_string(char **table, const char *s, size_t head, size_t tail)
{
	size_t	i;

	i = 0;
	*table = (char *)malloc(sizeof(char) * (tail - head + 1));
	if (*table == 0)
		return (0);
	while (i < tail - head)
	{
		(*table)[i] = s[i + head];
		i++;
	}
	(*table)[i] = '\0';
	return (1);
}

char	**free_split(char **table, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free(table[i++]);
	free(table);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**table;
	size_t	row;
	size_t	i;
	size_t	head;

	i = 0;
	row = 0;
	table = (char **)malloc(sizeof(char *) * (row_size(s, c) + 1));
	if (table == 0)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			head = i;
			while (s[i] != c && s[i])
				i++;
			if (!make_split_string(&(table[row++]), s, head, i))
				return (free_split(table, row - 1));
		}
	}
	table[row] = 0;
	return (table);
}
