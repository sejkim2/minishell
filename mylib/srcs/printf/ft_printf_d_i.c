/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:09:09 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/24 11:10:09 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	print(char *ar, int max_index, int fd)
{
	int	i;
	int	print_num;
	int	len;
	int	sum;

	i = max_index - 1;
	sum = 0;
	while (i >= 0)
	{
		print_num = ar[i--] + 48;
		len = write(fd, &print_num, 1);
		if (len == -1)
			return (-1);
		sum += len;
	}
	return (sum);
}

static int	check_sign(int n, int fd)
{
	int	r;

	if (n < 0)
	{
		r = (-1) * n;
		if (write(fd, "-", 1) == -1)
			return (-1);
	}
	else
		r = n;
	return (r);
}

static int	ft_putnbr_fd(int n, int fd)
{
	int		r;
	char	print_num[10];
	int		index;

	index = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	else if (n == 0)
		return (write(fd, "0", 1));
	else
	{
		r = check_sign(n, fd);
		if (r == -1)
			return (-1);
		while (r > 0)
		{
			print_num[index++] = r % 10;
			r = r / 10;
		}
		return (print(print_num, index, fd));
	}
}

int	ft_printf_d_i(int num)
{
	long long	n;
	int			len;

	n = num;
	len = 0;
	if (n == 0)
		return (write(1, "0", 1));
	len = ft_putnbr_fd(num, 1);
	if (len == -1 || n > 0 || num == -2147483648)
		return (len);
	else
		return (len + 1);
}
