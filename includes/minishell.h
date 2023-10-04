/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:22 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/04 19:58:34 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/ioctl.h>
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
# include <dirent.h>
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

/*main*/

/*lexer*/
t_linked_list *lexer(char *cmd_line);

/*list*/
t_linked_list	*make_list();
void	push_back_list(t_linked_list *list, t_token_node *node);
t_token_node *pop_list(t_linked_list *list);

/*node*/
t_token *make_token(void);
t_token_node	*make_node(t_token *token);

/*tokenize*/
t_token_node	*tokenize(char *cmd_line, int *index);

int parse_redirection(char *cmd_line, int *end, s_str_info **str_info);
int parse_word(char *cmd_line, int *end, t_token *token);
int parse_branket(char ch, int *end, t_token *token);
int parse_pipe_or_orif_or_andif(char *cmd_line, char ch, int *end, t_token *token);
char *make_value(char *cmd_line, int start, int end);
void parse_single_quote_string(char *cmd_line, int *end);
void parse_double_quote_string(char *cmd_line, int *end);

/*make_str_info*/
int count_quote_string(char *cmd_line, int start, int end);
s_str_info *make_quote_string(char *cmd_line, int start, int end);
void single_close_quote(char *cmd_line, int *start, int end);
void double_close_quote(char *cmd_line, int *start, int end);
void normal_string(char *cmd_line, int *start, int end);

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
/* heredoc signal */
void			set_heredoc_signal(void);
void			set_fork_heredoc_signal(void);
/* terminal option */
struct termios	terminal_option(void);
void			set_origin_signal(void);
void			set_terminal_print_off(void);
void			set_terminal_print_on(void);


/*error*/
void malloc_error();
int	print_unexpected_token_syntax_error(char *error_string, char error_ch);

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

int parse_error(char *error_string);

int parse_simple_command(t_linked_list *list, t_tree_node *parent);
int parse_simple_command_element(t_linked_list *list, t_tree_node *parent);
int parse_subshell(t_linked_list *list, t_tree_node *parent);
int parse_list(t_linked_list *list, t_tree_node *parent);
int parse_pipeline(t_linked_list *list, t_tree_node *parent);
int parse_command(t_linked_list *list, t_tree_node *parent);
int parse_redirection_list(t_linked_list *list, t_tree_node *parent);

char *free_tree_node(t_tree_node *node);
char *free_tree(t_tree_node *parent);


/*	built-in	*/
int 	func_cd(char **argv);
int	builtin_exit(int argc, char **argv, char **envp);


/*	built-in utils	*/
int		check_key_string(char *av);
int		is_equal(char *str);
char	**check_equation(char *av, char **env);
int		check_dup(char *av, char *env_name, char **env);
int		check_key_rule(char **av, char ***env);
char	**init_environ(char **envp);
char	*get_envname(char *av);
char	*get_envval(char *env_name, char **env);
void	make_new_env(int i, char **string, char **env);
void	change_env(t_tree_node *parent, char **env);
void	free_2str(char *s1, char *s2);
void	make_strings(int i, char **str, char **str_arr);
void	matrix_cpy(char **src, char **dst);
void	sort_ascii(char **envp, int cnt);
int		cnt_line(char **str_arr);
char	**add_export(char *av, char **env);
#endif