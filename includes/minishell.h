/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:22 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/25 15:56:14 by sejkim2          ###   ########.fr       */
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
# include "../mylib/includes/get_next_line.h"

typedef unsigned long long	t_ull;

typedef enum e_symbol
{
	WORD = 0,
	ASSIGNMENT_WORD,
	REDIRECTION,
    REDIRECTION_LIST,
	PIPE,
    AND_IF,
    OR_IF,
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

typedef enum s_redir_type
{
    NO_REDIR = 0,
    SINGLE_REDIR,
    DOUBLE_REDIR
}   t_redir;

typedef enum s_string_type
{
    NUL = 0,
    STRING,
    SINGLE_QUOTE,
    DOUBLE_QUOTE
}   t_str_type;

typedef struct s_string_info
{
    char *str;
    int str_len;
    t_str_type str_type;
}   s_str_info;

typedef struct s_token
{
    t_symbol symbol;
    t_redir redir_type;
    char *value;
    s_str_info *str_info;
}   t_token;

typedef struct s_token_node
{
	t_token				*token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_linkded_list
{
    int num_of_node;
    t_token_node *head;
    t_token_node *tail;
}   t_linked_list;

typedef struct s_tree_node
{
    t_symbol symbol;
    t_token *token;
    int num_of_child;
    struct s_tree_node *next;
    struct s_tree_node *child_list;
}   t_tree_node;

/*lexer*/
t_linked_list *lexer(char *cmd_line);

/*error*/
void lexer_error();

/*list*/
t_linked_list	*make_list();
void	push_back_list(t_linked_list *list, t_token_node *node);
t_token_node *pop_list(t_linked_list *list);

/*node*/
void	init_token(t_token *token, t_symbol symbol, char *value, t_redir type);
t_token	*make_token(t_symbol symbol, char *value, t_redir type, s_str_info **str_info);
t_token_node	*make_node(t_token *token);

/*tokenize*/
t_token_node	*tokenize(char *cmd_line, int *index);

t_symbol parse_redirection(char *cmd_line, int *end, s_str_info **str_info);
t_symbol parse_word(char *cmd_line, int *end, s_str_info **str_info);
t_symbol parse_branket(char ch, int *end);
t_symbol parse_pipe_or_orif_or_andif(char *cmd_line, char ch, int *end);
char *make_value(char *cmd_line, int start, int end);
void parse_single_quote_string(char *cmd_line, int *end);
void parse_double_quote_string(char *cmd_line, int *end);

/*make_str_info*/
int count_quote_string(char *cmd_line, int start, int end);
s_str_info *make_quote_string(char *cmd_line, int start, int end);
void single_close_quote(char *cmd_line, int *start, int end);
void double_close_quote(char *cmd_line, int *start, int end);
void normal_string(char *cmd_line, int *start, int end);

/*bit_mask*/
// int count_dollor_sign(char *cmd_line, int start, int end);
// int *make_bit_mask(char *cmd_line, int start, int end);

/*check_character_symbol*/
int check_is_single_quote(char ch);
int check_is_double_quote(char ch);
int check_is_white_space(char ch);
int check_is_meta_character(char ch);
int check_is_seperator(char ch);

/*check_close_quote*/
int check_is_close_quote(char *cmd_line, int index, char quote);

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


/*error*/
void malloc_error();
void	print_unexpected_token_syntax_error(char ch);

/*free*/
char *free_list(t_linked_list *list);
char *free_token_node(t_token_node *node);
char *free_token(t_token *token);

/*signal*/
void	set_shell_signal(void);
void	ctrl_c(int signum);
int		shell_ctrl_d(void);
void	set_terminal_print_off(void);
void	set_terminal_print_on(void);

/*parser*/
t_tree_node *parser(t_linked_list *list);

t_symbol next_symbol(t_linked_list *list);
int accept(t_linked_list *list, t_symbol symbol);
int expect(t_linked_list *list, t_symbol symbol);

void init_tree_node(t_linked_list *list, t_tree_node *node, t_symbol symbol);
t_tree_node *make_tree_node(t_linked_list *list, t_symbol symbol);
void addchild(t_tree_node *parent, t_tree_node *child);

void parse_error(void);

void parse_simple_command(t_linked_list *list, t_tree_node *parent);
void parse_simple_command_element(t_linked_list *list, t_tree_node *parent);
void parse_subshell(t_linked_list *list, t_tree_node *parent);
void parse_list(t_linked_list *list, t_tree_node *parent);
void parse_pipeline(t_linked_list *list, t_tree_node *parent);
void parse_command(t_linked_list *list, t_tree_node *parent);
void parse_redirection_list(t_linked_list *list, t_tree_node *parent);

char *free_tree_node(t_tree_node *node);
char *free_tree(t_tree_node *parent);


/*	built-in	*/
char			**init_environ(char **envp);
char			**change_env(char **av, char **env);
char			**rearrange_env(int cnt, char **env);
int				list_env(char **envp);
char			*skip_space_get_sign(char *str, int *sign);
void			init_val(t_ull *n, int *sign, int *cnt, int *flag);
unsigned char	ft_atol(char *str, int *flag);
int				list_export(char **envp);
int				set_env(char **argv, char **env);
void			func_unset(char **argv, char **env);
void			free_2str(char *s1, char *s2);
void			make_strings(int i, int j, char **av, char **str);
void			matrix_cpy(char **src, char **dst);
void			sort_ascii(char **envp, int cnt);
int				cnt_line(char **str_arr);
char			*get_envname(char *av);
char			*get_envval(char *env_name, char **env);
int				check_key_string(char *av);
char			**add_env(char *av, char **env);
char			**check_equation(char *av, char **env);
int				check_dup(char *av, char *env_name, char **env);
int				check_key_rule(char **av, char ***env);
int				is_equal(char *str);
#endif