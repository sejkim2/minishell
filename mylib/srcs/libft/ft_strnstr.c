/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:57:57 by sejkim2           #+#    #+#             */
/*   Updated: 2023/06/08 11:50:41 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_size;
	char	*str;
	char	*to_find;

	str = (char *)haystack;
	to_find = (char *)needle;
	needle_size = ft_strlen(needle);
	if (*to_find == 0)
		return (str);
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (i + j < len && j < needle_size && str[i + j] == to_find[j])
				j++;
			if (j == needle_size)
				return (str + i);
		}
		i++;
	}
	return (0);
}
