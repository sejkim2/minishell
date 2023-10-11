/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:36:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/25 17:07:54 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char	*p;
	size_t	i;
	size_t	len;

	p = (char *)s;
	i = 0;
	len = ft_strlen_gnl(s);
	while (i <= len)
	{
		if (*(p + i) == (char)c)
			return (p + i);
		else
			i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;
	char	*dest;

	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	i = 0;
	j = 0;
	dest = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (dest == 0)
		return (0);
	while (i < s1_len)
	{
		dest[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		dest[i++] = s2[j++];
	dest[i] = 0;
	return (dest);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	s_len;
	size_t	size;
	size_t	i;

	i = 0;
	s_len = ft_strlen_gnl(s);
	if (start >= s_len)
		size = 1;
	else if (s_len - start < len)
		size = s_len - start + 1;
	else
		size = len;
	dest = (char *)malloc(sizeof(char) * (size));
	if (dest == 0)
		return (0);
	while (i + 1 < size)
	{
		dest[i] = s[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*split_two_str(char **buf)
{
	char	*line;
	char	*tmp;
	char	*cur_newline;
	int		newline_index;

	tmp = *buf;
	cur_newline = ft_strchr_gnl(*buf, '\n');
	if (cur_newline == 0)
	{
		*buf = 0;
		return (tmp);
	}
	newline_index = cur_newline - *buf + 1;
	line = ft_substr_gnl(*buf, 0, newline_index + 1);
	if (line == 0)
		return (0);
	*buf = ft_substr_gnl(*buf, newline_index, ft_strlen_gnl(*buf));
	if (*buf == 0)
	{
		free(line);
		return (0);
	}
	free(tmp);
	return (line);
}
