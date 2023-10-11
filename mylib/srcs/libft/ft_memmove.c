/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:57:21 by sejkim2           #+#    #+#             */
/*   Updated: 2023/06/08 11:46:19 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == src)
		return (dst);
	if (dst < src)
		dst = ft_memcpy(dst, src, len);
	else
	{
		i = len;
		while (i-- > 0)
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
	}
	return (dst);
}
