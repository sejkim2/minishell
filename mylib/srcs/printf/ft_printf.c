/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:09:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/25 17:04:01 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	size_t	i;
	size_t	len;
	va_list	ap;
	int		count;
	int		size;

	va_start(ap, format);
	i = 0;
	count = 0;
	len = ft_strlen_printf(format);
	while (i < len)
	{
		if (format[i] == '%')
			size = ft_printf_conversions(format[++i], &ap);
		else
			size = ft_printf_c(format[i]);
		if (size == -1)
			return (-1);
		else
			count += size;
		i++;
	}
	va_end(ap);
	return (count);
}
