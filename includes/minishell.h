/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:22 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/13 15:02:28 by sejkim2          ###   ########.fr       */
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

/*lexer*/
t_linked_list *lexer(char *cmd_line);

/*node, list*/

/*tokenize*/
t_token_node	*tokenize(char *cmd_line, int *index);

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

#endif