/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_is_close_quote.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:37:29 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/25 20:37:33 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_is_close_quote(char *cmd_line, int index, char quote)
{
    index++;
    while (cmd_line[index])
    {
        if (cmd_line[index] == quote)
            break;
        index++;
    }
    if (cmd_line[index] == quote)
        return (1);
    else
        return (0);
}