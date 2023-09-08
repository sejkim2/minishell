/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:22 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/08 18:56:57 by sejkim2          ###   ########.fr       */
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
# include <termios.h>
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

/*트리 심볼(임시)*/
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
    char *cmd_line;
    int num_of_node;
    t_token_node *head;
    t_token_node *tail;
}   t_linked_list;

typedef struct s_tree_node
{
    t_linked_list *list;
    t_tree_symbol node_symbol;
    int blanket_flag;
    struct s_tree_node *sub_tree;   //if token list include ()
    struct s_tree_node *left_child;
    struct s_tree_node *right_child;
}   t_tree_node;

typedef struct s_tree_manager
{
    t_tree_node *root_node;
    int num_of_node;    //or num_of_leaf_node
}   t_tree_manager;

/*lexer*/
t_linked_list *lexer(char *cmd_line);

/*node, list*/
t_token_node *make_node(char *str, t_type check_type);
t_linked_list *make_list(char *cmd_line);
void push_back_list(t_linked_list *list, t_token_node *node);

/*tokenize*/
void tokenize(t_linked_list *list, char *cmd_line, int *i, t_type *token_type);
int check_is_meta_character(char *cmd_line, int index);
int check_is_quote(char *cmd_line, int index);
int check_is_white_space(char *cmd_line, int index);
int check_is_seperator(char *cmd_line, int index);

/*free*/
char *free_list(t_linked_list *list);
char *free_node(t_token_node *node);
char *free_token(t_token *token);

/*signal*/
void	set_shell_signal(void);
void	ctrl_c(int signum);
int		ctrl_d(void);
void	set_terminal_print_off(void);
void	set_terminal_print_on(void);



#endif