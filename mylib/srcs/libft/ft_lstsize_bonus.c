/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:57:11 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/24 11:08:28 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*p;
	int		count;

	p = lst;
	count = 0;
	while (p)
	{
		count++;
		p = p->next;
	}
	return (count);
}
