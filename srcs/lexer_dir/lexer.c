/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/04 18:46:21 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_blank_error(t_linked_list *list)
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
		{
			printf("minishell: syntax error unmatched parentheses\n");
			return (-1);
		}
		if (cur->next)
		{
			if (cur->token->symbol == L_BRA && cur->next->token->symbol == R_BRA)
				return (print_unexpected_token_syntax_error(0, ')'));
		}
		cur = cur->next;
	}
	if (cnt_l_bra != cnt_r_bra)
	{
		printf("minishell: syntax error unmatched parentheses\n");
		return (-1);
	}
	else
		return (1);
}

static	void	print_list(t_linked_list *list)
{
	t_token_node	*cur;

	cur = list->head;
	while (cur)
	{
		printf("[ symbol : %d value : %s]", cur->token->symbol, cur->token->value);
		if (cur->token->str_info != 0)
		{
			int i = 0;
			printf("[");
			while (cur->token->str_info[i].str_type != NUL)
			{
				printf("str : %s , type : %d ", cur->token->str_info[i].str, cur->token->str_info[i].str_type);
				i++;
			}
			printf("]");
		}
		else
			printf("[str is meta]");
		if (cur->token->redir_type == SINGLE_REDIR)
			printf("[single redir]");
		else if(cur->token->redir_type == DOUBLE_REDIR)
			printf("[double redir]");
		else if (cur->token->redir_type == NO_REDIR)
			printf("[no redir]");
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
	while (cmd_line[i])
	{
		while (cmd_line[i] && check_is_white_space(cmd_line[i]))
			i++;
		if (!cmd_line[i])
			break ;
		node = tokenize(cmd_line, &i);
		if (node == 0)
		{
			free_list(list);
			return (0);
		}
		push_back_list(list, node);
	}
	if (list->num_of_node == 0)
	{
		free_list(list);
		return (0);
	}
	if (check_blank_error(list) == -1)
	{
		free_list(list);
		return (0);
	}
	print_list(list);
	return (list);
}
