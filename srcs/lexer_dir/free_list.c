/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:55:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/06 13:35:27 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*free_str_info(s_str_info *str_info)
{
	int	i;

	i = 0;
	while (str_info[i].str_type != NUL)
	{
		free(str_info[i].str);
		i++;
	}
	free(str_info);
	return (0);
}

char	*free_token(t_token *token)
{
	if (token->value)
		free(token->value);
	if (token->str_info)
		free_str_info(token->str_info);
	free(token);
	return (0);
}

char	*free_token_node(t_token_node *node)
{
	free_token(node->token);
	node->next = 0;
	free(node);
	return (0);
}

char	*free_list(t_linked_list *list)
{
	t_token_node	*cur;
	t_token_node	*del_node;

	cur = list->head;
	list->head = 0;
	list->tail = 0;
	if (list->num_of_node == 0)
	{
		free(list);
		return (0);
	}
	while (cur->next)
	{
		del_node = cur;
		cur = cur->next;
		free_token_node(del_node);
	}
	if (cur)
		free_token_node(cur);
	free(list);
	return (0);
}