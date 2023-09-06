/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/06 18:41:15 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	print_list(t_linked_list *list)
{
	t_token_node	*cur;

	cur = list->head;
	while (cur)
	{
		printf("[ token : %s type : %d]\n", \
		cur->token->token_value, cur->token->token_type);
		cur = cur->next;
	}
}

t_linked_list	*lexer(char *cmd_line)
{
	int				i;
	t_linked_list	*list;
	t_type			token_type;

	i = 0;
	list = make_list(cmd_line);
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
		token_type = WORD;
		tokenize(list, cmd_line, &i, &token_type);
	}
	print_list(list);
	return (list);
}
