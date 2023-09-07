/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:57:18 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/07 19:04:28 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void parser(t_linked_list *list)
{
    t_token_node *cur;
    t_linked_list *simple_cmd;

    cur = list->head;
    simple_cmd = make_list(0);
    while (cur)
    {
        if (cur->token->token_type == AND_IF || cur->token->token_type == OR_IF)
        {
            
        }
        else if (cur->token->token_type == LEFT_BLANKET || cur->token->token_type == RIGHT_BLANKET)
        {

        }
        else    //simple command
            push_back_list(simple_cmd, cur);
        cur = cur->next;
    }
}