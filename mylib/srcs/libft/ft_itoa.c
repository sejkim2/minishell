/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:55:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/06/08 11:51:33 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	len_num(const int n)
{
	long long	num;
	int			is_minus;
	int			len;

	is_minus = 0;
	num = n;
	len = 0;
	if (n <= 0)
	{
		is_minus = 1;
		num = (long long)-1 * (n);
	}
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	return (len + is_minus);
}

char	*num_to_string(char *dest, int n, int len)
{
	long long	num;
	int			i;

	i = len;
	dest[i--] = '\0';
	num = (long long)n;
	if (num == 0)
	{
		dest[0] = '0';
		return (dest);
	}
	else if (num < 0)
	{
		dest[0] = '-';
		num = (-1) * num;
	}
	while (num > 0)
	{
		dest[i--] = num % 10 + '0';
		num = num / 10;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;

	len = len_num(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == 0)
		return (0);
	dest = num_to_string(dest, n, len);
	return (dest);
}
