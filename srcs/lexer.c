/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/12 20:08:27 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static	void	print_list(t_linked_list *list)
// {
// 	t_token_node	*cur;

// 	cur = list->head;
// 	while (cur)
// 	{
// 		printf("[ token : %s type : %d]\n", \
// 		cur->token->token_value, cur->token->token_type);
// 		cur = cur->next;
// 	}
// }

t_linked_list	*lexer(char *cmd_line)
{
	int				i;
	t_linked_list	*list;
	t_token_node	*node;

	i = 0;
	list = make_list();
	if (list == 0)
	{
		write(2, "malloc error\n", 13);
		free(cmd_line);
		exit(1);
	}
	while (cmd_line[i])
	{
		while (cmd_line[i] && check_is_white_space(cmd_line, i))
			i++;
		if (!cmd_line[i])
			break ;
		node = tokenize(cmd_line, &i);
		push_back_list(list, node);
	}
	// print_list(list);
	return (list);
}
