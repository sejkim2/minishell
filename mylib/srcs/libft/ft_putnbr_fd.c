/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:57:30 by sejkim2           #+#    #+#             */
/*   Updated: 2023/06/08 11:46:45 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	print(char *ar, int max_index, int fd)
{
	int	i;
	int	print_num;

	i = max_index - 1;
	while (i >= 0)
	{
		print_num = ar[i--] + 48;
		write(fd, &print_num, 1);
	}
}

int	check_sign(int n, int fd)
{
	int	r;

	if (n < 0)
	{
		r = (-1) * n;
		write(fd, "-", 1);
	}
	else
		r = n;
	return (r);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		r;
	char	print_num[10];
	int		index;

	index = 0;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		r = check_sign(n, fd);
		while (r > 0)
		{
			print_num[index++] = r % 10;
			r = r / 10;
		}
		print(print_num, index, fd);
	}
}
