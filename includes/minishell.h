/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:22 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/13 19:42:34 by jaehyji          ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <curses.h>
// # include "../readline_dir/include/readline/readline.h"
// # include "../readline_dir/include/readline/history.h"
# include <readline/readline.h>
# include <readline/history.h>
// # include "../readline/include/readline/readline.h"
// # include "../readline/include/readline/history.h"
# include "../mylib/includes/libft.h"

typedef unsigned long long	t_ull;

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
}	t_type;

typedef enum e_tree_symbol
{
	EXPRESS = 0,
	PIPELINE
}	t_tree_symbol;

typedef struct s_token
{
	t_type	token_type;
	char	*token_value;
}	t_token;

typedef struct s_token_node
{
	t_token				*token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_linkded_list
{
	char			*cmd_line;
	int				num_of_node;
	t_token_node	*head;
	t_token_node	*tail;
}	t_linked_list;

typedef struct s_tree_node
{
	t_linked_list		*list;
	t_tree_symbol		node_symbol;
	struct s_tree_node	*parent;
	struct s_tree_node	*left_child;
	struct s_tree_node	*right_child;
}	t_tree_node;

t_linked_list	*lexer(char *cmd_line);
t_token_node	*make_node(char *cmd_line, \
int start, int end, t_type check_type);
t_linked_list	*make_list(char *cmd_line);
void			push_back_list(t_linked_list *list, t_token_node *node);

void			tokenize(t_linked_list *list, \
char *cmd_line, int *i, t_type *token_type);
int				check_is_meta_character(char *cmd_line, int index);
int				check_is_quote(char *cmd_line, int index);
int				check_is_white_space(char *cmd_line, int index);
int				check_is_seperator(char *cmd_line, int index);

char			*free_list(t_linked_list *list);
char			*free_node(t_token_node *node);
char			*free_token(t_token *token);

/* shell signal */
void			set_shell_signal(int *cursor);
void			shell_ctrl_c(int signum);
int				shell_ctrl_d(int cursor);

/* blocking signal */
void			set_blocking_signal(void);
void			check_blocking_signal(void);
void			blocking_ctrl_c(int signum);
void			blocking_ctrl_backslash(int signum);
/* heredoc signal */
void			set_heredoc_signal(void);
void			check_heredoc_signal(int *cursor);
void			heredoc_ctrl_c(int signum);
/* terminal option */
struct termios	terminal_option(void);
void			set_origin_signal(void);
void			set_terminal_print_off(void);
void			set_terminal_print_on(void);

/*	env	*/
char	**change_env(char **argv);
#endif