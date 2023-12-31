/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/25 15:17:27 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_arithmetic_expansion(t_linked_list *list)
{
	int				flag;
	t_token_node	*cur;

	flag = 0;
	cur = list->head;
	while (cur)
	{
		if (cur->token->symbol == L_BRA)
		{
			cur = cur->next;
			if (cur && cur->token->symbol == L_BRA)
				flag = 1;
		}
		else if (cur->token->symbol == R_BRA)
		{
			cur = cur->next;
			if (cur && cur->token->symbol == R_BRA)
				if (flag == 1)
					return (print_arithmetic_expansion_syntax_error());
		}
		else
			cur = cur->next;
	}
	return (1);
}

static int	check_blank_error(t_linked_list *list)
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
		if (cnt_l_bra < cnt_r_bra)
			return (print_unmatched_parentheses_syntax_error());
		cur = cur->next;
	}
	if (cnt_l_bra != cnt_r_bra)
		return (print_unmatched_parentheses_syntax_error());
	else
		return (1);
}

static int	check_list_is_empty_or_blank_error(t_linked_list *list)
{
	if (list->num_of_node == 0 || check_blank_error(list) == -1 \
	|| check_arithmetic_expansion(list) == -1)
	{
		free_list(list, 1);
		return (0);
	}
	else
		return (1);
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
		if (node == 0)
		{
			free_list(list, 1);
			return (0);
		}
		push_back_list(list, node);
	}
	if (check_list_is_empty_or_blank_error(list))
		return (list);
	else
		return (0);
}
