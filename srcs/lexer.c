/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/22 15:19:22 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	check_blank_error(t_linked_list *list)
{
	int				cnt_l_bra;
	int				cnt_r_bra;
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
		printf("[ symbol : %d value : %s]", \
		cur->token->symbol, cur->token->value);
		if (cur->token->bit_mask != 0)
		{
			int i = 0;
			printf("[");
			while (cur->token->bit_mask[i] > -1)
			{
				printf("bit : %d ", cur->token->bit_mask[i]);
				i++;
			}
			printf("]");
		}
		else
			printf("[bit is null]");
		if (cur->token->redir_type == SINGLE_REDIR)
			printf("[single redir]");
		else if(cur->token->redir_type == DOUBLE_REDIR)
			printf("[double redir]");
		printf("\n");
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
	if (list == 0)
		malloc_error();
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
