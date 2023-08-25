/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:57:06 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/24 11:08:23 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstclear_func(t_list **lst, void (*del)(void *), void *cont)
{
	t_list	*p;
	t_list	*del_node;

	p = *lst;
	*lst = 0;
	while (p)
	{
		del_node = p;
		p = p->next;
		del(del_node->content);
		free(del_node);
	}
	free(cont);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*new;
	t_list	*head;
	t_list	*tail;
	void	*cont;

	p = lst;
	head = 0;
	tail = head;
	while (p)
	{
		cont = f(p->content);
		if (cont == 0)
			return (ft_lstclear_func(&head, del, cont));
		new = ft_lstnew(cont);
		if (new == 0)
			return (ft_lstclear_func(&head, del, cont));
		if (tail == 0)
			head = new;
		else
			tail->next = new;
		tail = new;
		p = p->next;
	}
	return (head);
}
