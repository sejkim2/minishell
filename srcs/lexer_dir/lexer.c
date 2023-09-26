/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/25 20:36:39 by sejkim2          ###   ########.fr       */
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
		cur = cur->next;
	}
	if (cnt_l_bra != cnt_r_bra)
		return (print_unexpected_token_syntax_error('\n'));	//message 수정 필요
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
	if (list == 0)
		malloc_error();
	while (cmd_line[i])
	{
		while (cmd_line[i] && check_is_white_space(cmd_line[i]))
			i++;
		if (!cmd_line[i])
			break ;
		node = tokenize(cmd_line, &i);
		if (node == 0)
			return (0);
		push_back_list(list, node);
	}
	if (check_blank_error(list) == -1)
		return (0);
	print_list(list);
	return (list);
}
