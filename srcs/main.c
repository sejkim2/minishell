/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/08/29 19:39:08 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void handler(int signum)
// {
//     if (signum != SIGINT)
//         return ;
//     write(STDOUT_FILENO, "\n", 1);
//     if (rl_on_new_line() == -1)
//         exit(1);
//     rl_replace_line("", 1);
//     rl_redisplay();
// }

int main(void)
{
    char *line;
    t_linked_list *list;

    // signal(SIGINT, handler);
    while (1)
    {
        line = readline("minishell> ");
        if (line)
        {
            add_history(line);
            list = lexer(line);
            parser(list);
            // free(list);
            free(line);
            line = 0;
        }
        else
            exit(1);
    }
    return (0);
}
