/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:57:23 by sejkim2           #+#    #+#             */
/*   Updated: 2023/06/08 11:46:23 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	void	*p;

	i = 0;
	p = b;
	while (i < len)
	{
		*((unsigned char *)p + i) = (unsigned char)c;
		i++;
	}
	return (b);
}
