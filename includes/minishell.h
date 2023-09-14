/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:22 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/14 19:54:00 by sejkim2          ###   ########.fr       */
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

typedef enum e_symbol
{
	WORD = 0,
	ASSIGNMENT_WORD,
	REDIRECTION,
	PIPE,
    AND_IF,
    OR_IF,
    EQUAL,
    L_BRA,
    R_BRA,
    SIMPLE_COMMAND_ELEMENT,
    SIMPLE_COMMAND,
    COMMAND,
    PIPELINE,
    SUBSHELL,
    LIST,
    ROOT
}   t_symbol;

typedef struct s_token
{
    t_symbol symbol;
    char *value;
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
    t_symbol symbol;
    int num_of_child;
    struct s_tree_node *next;
    struct s_tree_node *child_list;
}   t_tree_node;

/*lexer*/
t_linked_list *lexer(char *cmd_line);

/*list*/
t_linked_list	*make_list();
void	push_back_list(t_linked_list *list, t_token_node *node);
t_token_node *pop_list(t_linked_list *list);

/*node*/
void	init_token(t_token *token, t_symbol symbol, char *value);
t_token	*make_token(t_symbol symbol, char *value);
t_token_node	*make_node(t_token *token);

/*tokenize*/
t_token_node	*tokenize(char *cmd_line, int *index);

t_symbol parse_redirection(char *cmd_line, int *end);
t_symbol parse_word(char *cmd_line, int *end);
t_symbol parse_equal_or_branket(char ch, int *end);
t_symbol parse_pipe_or_orif_or_andif(char ch, char next_ch, int *end);
char *make_value(char *cmd_line, int start, int end);
void parse_single_quote_string(char *cmd_line, int *end);
void parse_double_quote_string(char *cmd_line, int *end);

/*check_character_symbol*/
int check_is_single_quote(char ch);
int check_is_double_quote(char ch);
int check_is_white_space(char ch);
int check_is_meta_character(char ch);
int check_is_seperator(char ch);

/*free*/
// char *free_list(t_linked_list *list);
// char *free_node(t_token_node *node);
// char *free_token(t_token *token);

/*signal*/
void	set_shell_signal(void);
void	ctrl_c(int signum);
int		ctrl_d(void);
void	set_terminal_print_off(void);
void	set_terminal_print_on(void);

/*parser*/
void parser(t_linked_list *list);

void parse_simple_command(t_linked_list *list, t_tree_node *parent);
void parse_simple_command_element(t_linked_list *list, t_tree_node *parent);
void parse_subshell(t_linked_list *list, t_tree_node *parent);
void parse_list(t_linked_list *list, t_tree_node *parent);
void parse_pipeline(t_linked_list *list, t_tree_node *parent);
void parse_command(t_linked_list *list, t_tree_node *parent);


#endif