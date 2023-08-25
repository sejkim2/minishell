/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:57:38 by sejkim2           #+#    #+#             */
/*   Updated: 2023/06/08 11:47:53 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	size_t	i;
	size_t	len;

	p = (char *)s;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (*(p + i) == (char)c)
			return (p + i);
		else
			i++;
	}
	return (0);
}
