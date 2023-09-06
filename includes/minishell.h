/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:22 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/06 16:43:48 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <term.h>
# include <unistd.h>
// # include "../readline_dir/include/readline/readline.h"
// # include "../readline_dir/include/readline/history.h"
# include <readline/readline.h>
# include <readline/history.h>
// # include "../readline/include/readline/readline.h"
// # include "../readline/include/readline/history.h"
# include "../mylib/includes/libft.h"

typedef enum e_type
{
	WORD = 0,
	PIPE,
	AND_IF,
	OR_IF,
    IN_REDIRECTION,
    OUT_REDIRECTION,
    HEREDOC,
    APPEND,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    LEFT_BLANKET,
    RIGHT_BLANKET,
    DOLLOR_SIGN
}   t_type;

typedef enum e_tree_symbol
{
    EXPRESS = 0,
    PIPELINE
}   t_tree_symbol;

typedef struct s_token
{
    t_type token_type;
    char *token_value;
}   t_token;

typedef struct s_token_node
{
    t_token *token;
    struct s_token_node *next;
}   t_token_node;

typedef struct s_linkded_list
{
    int num_of_node;
    t_token_node *head;
    t_token_node *tail;
}   t_linked_list;

typedef struct s_tree_node
{

    t_linked_list *list;
    t_tree_symbol node_symbol;
    struct s_tree_node *parent;
    struct s_tree_node *left_child;
    struct s_tree_node *right_child;
}   t_tree_node;

t_linked_list *lexer(char *cmd_line);


#endif