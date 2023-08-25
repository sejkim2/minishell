/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:58:06 by sejkim2           #+#    #+#             */
/*   Updated: 2023/06/08 11:49:42 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	s_len;
	size_t	size;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		dest = (char *)malloc(sizeof(char) * 1);
		if (dest == 0)
			return (0);
		*dest = 0;
		return (dest);
	}
	if (s_len - start < len)
		size = s_len - start;
	else
		size = len;
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == 0)
		return (0);
	ft_strlcpy(dest, s + start, size + 1);
	return (dest);
}
