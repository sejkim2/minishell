/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/06 19:19:02 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    char *line;
    t_linked_list *list;

    while (1)
    {
        line = readline("minishell> ");
        if (line)
        {
            add_history(line);
            list = lexer(line);
            free_list(list);
            line = 0;
        }
        else
            exit(1);
    }
    return (0);
}
