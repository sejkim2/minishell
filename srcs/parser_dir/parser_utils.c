/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:03:03 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/18 16:01:37 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_symbol	next_symbol(t_linked_list *list)
{
	t_token_node	*node;
	t_symbol		symbol;

	node = pop_list(list);
	symbol = node->token->symbol;
	return (symbol);
}

int	accept(t_linked_list *list, t_symbol symbol)
{
	if (list->num_of_node == 0)
		return (0);
	return (list->head->token->symbol == symbol);
}

int	expect(t_linked_list *list, t_symbol symbol)
{
	if (!accept(list, symbol))
		return (parse_error(list->head->token->value));
	else
		return (1);
}
