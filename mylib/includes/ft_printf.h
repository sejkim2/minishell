/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:09:30 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/25 17:05:44 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_printf_conversions(char ch, va_list *ap);
int		ft_printf_c(char ch);
int		ft_printf_s(char *s);
int		ft_printf_p(void *addr);
int		ft_printf_d_i(int num);
int		ft_printf_u(int num);
int		ft_printf_x(int num, char base);
int		ft_printf(const char *format, ...);
int		ft_putnbr_base(size_t nbr, char *base);
size_t	ft_strlen_printf(const char *s);

#endif
