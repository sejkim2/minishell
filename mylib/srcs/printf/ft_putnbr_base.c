/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:09:37 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/25 17:03:55 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static	int	print_num(size_t num, char *base, size_t order)
{
	char	print_num[16];
	size_t	r;
	int		index;
	int		sum;
	int		len;

	sum = 0;
	r = num;
	index = 0;
	while (r > 0)
	{
		print_num[index++] = base[r % order];
		r = r / order;
	}
	index--;
	while (index >= 0)
	{
		len = write(1, print_num + index, 1);
		if (len == -1)
			return (-1);
		sum += len;
		index--;
	}
	return (sum);
}

static	size_t	is_valid(char *base)
{
	size_t	i;
	size_t	j;
	size_t	base_len;

	base_len = ft_strlen_printf(base);
	if (base_len <= 1)
		return (0);
	i = 0;
	while (i < base_len)
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (j < base_len)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (base_len);
}

int	ft_putnbr_base(size_t nbr, char *base)
{
	size_t	num;
	size_t	order;

	num = nbr;
	order = is_valid(base);
	if (order == 0)
		return (-1);
	if (num == 0)
		return (write(1, &base[0], 1));
	else
		return (print_num(num, base, order));
}
