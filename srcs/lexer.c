/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/13 15:03:45 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static t_linked_list	*make_list()
{
	t_linked_list	*new_list;

	new_list = (t_linked_list *)malloc(sizeof(t_linked_list));
	if (new_list == 0)
		return (0);

	new_list->num_of_node = 0;
	new_list->head = 0;
	new_list->tail = 0;
	return (new_list);
}

static void	push_back_list(t_linked_list *list, t_token_node *node)
{
	// if (node == 0)
	// {
	// 	free_list(list);
	// 	exit(1);
	// }
	if (list->num_of_node == 0)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->num_of_node++;
}

static int check_is_white_space(char ch)
{
	if (ch == '\t' || ch == ' ')
		return (1);
	else
		return (0);
}

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
		while (cmd_line[i] && check_is_white_space(cmd_line[i]))
			i++;
		if (!cmd_line[i])
			break ;
		node = tokenize(cmd_line, &i);
		push_back_list(list, node);
	}
	print_list(list);
	return (list);
}
