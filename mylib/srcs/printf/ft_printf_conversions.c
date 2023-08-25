/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:08:56 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/24 11:10:07 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_printf_conversions(const char ch, va_list *ap)
{
	if (ch == 'c')
		return (ft_printf_c(va_arg(*ap, int)));
	else if (ch == 's')
		return (ft_printf_s(va_arg(*ap, char *)));
	else if (ch == 'p')
		return (ft_printf_p(va_arg(*ap, void *)));
	else if (ch == 'd' || ch == 'i')
		return (ft_printf_d_i(va_arg(*ap, int)));
	else if (ch == 'u')
		return (ft_printf_u(va_arg(*ap, int)));
	else if (ch == 'x' || ch == 'X')
		return (ft_printf_x(va_arg(*ap, int), ch));
	else if (ch == '%')
		return (ft_printf_c('%'));
	else
		return (-1);
}
