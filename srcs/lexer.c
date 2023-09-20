/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 13:42:23 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void check_blank_error(t_linked_list *list)
{
	int cnt_l_bra;
	int cnt_r_bra;
	t_token_node	*cur;

	cnt_l_bra = 0;
	cnt_r_bra = 0;
	cur = list->head;
	while (cur)
	{
		if (cur->token->symbol == L_BRA)
			cnt_l_bra++;
		else if (cur->token->symbol == R_BRA)
			cnt_r_bra++;
		cur = cur->next;
	}
	if (cnt_l_bra != cnt_r_bra)
		lexer_error();
}

static	void	print_list(t_linked_list *list)
{
	t_token_node	*cur;

	cur = list->head;
	while (cur)
	{
		printf("[ symbol : %d value : %s]\n", \
		cur->token->symbol, cur->token->value);
		cur = cur->next;
	}
}

t_linked_list	*lexer(char *cmd_line)
{
	int				i;
	t_linked_list	*list;
	t_token_node	*node;

	i = 0;
	list = make_list();
	while (cmd_line[i])
	{
		while (cmd_line[i] && check_is_white_space(cmd_line[i]))
			i++;
		if (!cmd_line[i])
			break ;
		node = tokenize(cmd_line, &i);
		push_back_list(list, node);
	}
	check_blank_error(list);
	print_list(list);
	return (list);
}
