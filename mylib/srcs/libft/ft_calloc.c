/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:56:27 by sejkim2           #+#    #+#             */
/*   Updated: 2023/06/08 11:43:37 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *)malloc(count * size);
	if (p == 0)
		return (0);
	while (i < count * size)
		p[i++] = 0;
	return (p);
}
