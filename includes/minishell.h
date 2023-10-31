/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:22 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/31 11:35:06 by jaehyji          ###   ########.fr       */
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
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../mylib/includes/libft.h"
# include "../mylib/includes/get_next_line.h"

typedef unsigned long long	t_ull;
extern char					**environ;
unsigned char				g_exit_status;

/*		define struct		*/

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
}	t_symbol;

typedef enum s_redir_type
{
	NO_REDIR = 0,
	SINGLE_REDIR,
	DOUBLE_REDIR
}	t_redir;

typedef enum s_string_type
{
	NUL = 0,
	STRING,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_str_type;

typedef struct s_string_info
{
	char		*str;
	int			str_len;
	t_str_type	str_type;
}	t_str_info;

typedef struct s_token
{
	t_symbol	symbol;
	t_redir		redir_type;
	char		*value;
	char		*hd_name;
	t_str_info	*str_info;
}	t_token;

typedef struct s_token_node
{
	t_token				*token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_linkded_list
{
	int				num_of_node;
	t_token_node	*head;
	t_token_node	*tail;
}	t_linked_list;

typedef struct s_tree_node
{
	int					in_fork;
	t_symbol			symbol;
	t_token				*token;
	int					num_of_child;
	struct s_tree_node	*next;
	struct s_tree_node	*child_list;
}	t_tree_node;

typedef struct s_cmd
{
	char	*input;
	char	*cmd;
	char	**cmd_line;
}	t_cmd;

typedef struct s_env_str
{
	char	*fstr;
	char	*env_str;
	char	*bstr;
}	t_env_str;

/*				builtin_dir				*/
/*builtin*/
void			builtin_cd(char **cmd_argv, char **env);
void			builtin_echo(char **cmd_argv);
void			builtin_env(char **cmd_argv, char **env);
void			builtin_exit(char **cmd_argv, t_tree_node *root);
void			builtin_export(char **cmd_argv, char ***env);
void			builtin_pwd(void);
void			builtin_unset(char **cmd_argv, char ***env);

/*builtin_utils*/
int				check_unset_key_string(char *argv);
int				check_unset_key_rule(char *argv);
int				cnt_size(char **env, int cnt);
char			**rearrange_env(int cnt, char **env);
void			compare_envname(char *unset_name, char ***env, int cnt);
void			sort_ascii(char **envp, int cnt);
void			print_export(int i, char *env_name, char *env_val, char **env);
void			list_export(char **env);
void			matrix_cpy(char **dest, char **origin);
int				cnt_line(char **str_arr);
void			free_2str(char *s1, char *s2);
void			free_4str(char *s1, char *s2, char *s3, char *s4);
void			free_arr(char **arr);
void			check_malloc_fail(char *buff);
void			ft_stderror_print(char *cmd, char *argv, char *err_string);
void			list_env(char **env, char **cmd_argv);
void			set_env(char **cmd_argv, char **env);
void			check_env_dup(char **env, char **cmd_argv);
void			env_argv_error(char *argv, int error_code);
char			**check_argv_dup2(int cnt, char **cmd_argv_cpy);
char			**check_argv_dup1(char **cmd_argv);

/*env_utils*/
char			**init_setting(char **envp, int *o_fd);
char			*get_envname(char *av);
char			*get_envval(char *env_name, char **env);
char			*exit_status_env(int *i, char *line);
char			*expand_env(int *i, int len, char *line, char **env);
char			*check_env_case(int *i, char *line, char **env);
char			*parser_env(char *line, char **env);
int				get_envname_idx(int *i, char *line);
int				check_key_rule(char **cmd_argv, char ***env);
void			parser_env_in_tree(t_tree_node *parent, char **env);
char			*check_redir(t_tree_node *node);
char			*apply_in_tree(t_tree_node *node);

/*				lexer_dir				*/
/*check_character_symbol*/
int				check_is_single_quote(char ch);
int				check_is_double_quote(char ch);
int				check_is_white_space(char ch);
int				check_is_meta_character(char ch);
int				check_is_seperator(char ch);

/*free_list*/
char			*free_list(t_linked_list *list, int is_remove_token);
char			*free_token_node(t_token_node *node, int is_remove_token);
char			*free_token(t_token *token);

/*lexer_error*/
void			malloc_error(void);
void			system_call_error(void);
int				print_unexpected_token_syntax_error(char *error_string, \
char error_ch);
int				print_unmatched_parentheses_syntax_error(void);
int				print_arithmetic_expansion_syntax_error(void);

/*lexer*/
t_linked_list	*lexer(char *cmd_line);

/*list_node_utils*/
t_token			*make_token(void);
t_token_node	*make_node(t_token *token);

/*list_utils*/
t_linked_list	*make_list(void);
void			push_back_list(t_linked_list *list, t_token_node *node);
t_token_node	*pop_list(t_linked_list *list);

/*make_quote_string*/
t_str_info		*make_quote_string(char *cmd_line, int start, int end);

/*make_value*/
char			*make_value(char *cmd_line, int start, int end);

/*parse_pipe_or_orif_or_andif*/
int				parse_pipe_or_orif_or_andif(char *cmd_line, char ch, \
int *end, t_token *token);

/*parse_quote_string*/
void			parse_single_quote_string(char *cmd_line, int *end);
void			parse_double_quote_string(char *cmd_line, int *end);

/*parse_redirection*/
int				parse_redirection(char *cmd_line, int *end, \
t_str_info **str_info);

/*parse_word_or_branket*/
int				parse_word(char *cmd_line, int *end, t_token *token);
int				parse_branket(char ch, int *end, t_token *token);

/*quote_utils*/
int				count_quote_string(char *cmd_line, int start, int end);
void			single_close_quote(char *cmd_line, int *start, int end);
void			double_close_quote(char *cmd_line, int *start, int end);
void			normal_string(char *cmd_line, int *start, int end);
int				check_is_close_quote(char *cmd_line, int index, char quote);

/*tokenize*/
t_token_node	*tokenize(char *cmd_line, int *index);

/*				parser_dir				*/
/*free_tree*/
char			*free_tree_node(t_tree_node *node, int is_remove_token);
char			*free_tree(t_tree_node *parent, int is_remove_token);

/*parser_error*/
int				parse_error(char *error_string);

/*parser_function_1*/
int				parse_subshell(t_linked_list *list, \
t_tree_node *parent, char **env);
int				parse_pipeline(t_linked_list *list, \
t_tree_node *parent, char **env);
int				parse_list(t_linked_list *list, \
t_tree_node *parent, char **env);

/*parser_function_2*/
int				parse_simple_command(t_linked_list *list, \
t_tree_node *parent, char **env);
int				parse_simple_command_element(t_linked_list *list, \
t_tree_node *parent);
int				parse_command(t_linked_list *list, \
t_tree_node *parent, char **env);
int				parse_redirection_list(t_linked_list *list, \
t_tree_node *parent, char **env);

/*parser_utils*/
t_symbol		next_symbol(t_linked_list *list);
int				accept(t_linked_list *list, t_symbol symbol);
int				expect(t_linked_list *list, t_symbol symbol);

/*parser*/
t_tree_node		*parser(t_linked_list *list, char **env);

/*tree_node_utils*/
void			init_tree_node(t_linked_list *list, t_tree_node *node, \
t_symbol symbol);
t_tree_node		*make_tree_node(t_linked_list *list, t_symbol symbol);
void			addchild(t_tree_node *parent, t_tree_node *child);

/*				run_dir				*/
/*get_path*/
char			*get_path(char *exe, char **env);
char			*init_path_env(char *cmd, char **path);

/*run_root*/
void			run_root(t_tree_node *root, char ***env);

/*run_list*/
void			run_list(t_tree_node *node, char ***env, t_tree_node *root);
void			run_andif_list(t_tree_node *node, \
char ***env, t_tree_node *root);
void			run_orif_list(t_tree_node *node, \
char ***env, t_tree_node *root);

/*run_pipeline*/
void			run_pipeline(t_tree_node *node, \
char ***env, t_symbol before, t_tree_node *root);
void			run_pipe(t_tree_node *child, char ***env, t_tree_node *root);

/*run_command*/
void			run_command_nonpipe(t_tree_node *node, \
char ***env, t_tree_node *root);
void			run_command_pipe(t_tree_node *node, \
char ***env, t_tree_node *root);

/*run_simple_command*/
void			run_simple_command(t_tree_node *node, \
char ***env, t_tree_node *root);
void			free_cmd(t_cmd *cmd_info);

/*run_redir_utils*/
char			*set_redir_file_name(t_tree_node *node);
int				wild_card_error(char *input, int cnt);
int				open_error(char *redir_name);

/*run_redir*/
int				run_redirection_list(t_tree_node *node, char ***env);

/*run_exe*/
int				run_builtin(t_cmd cmd_info, char ***env, t_tree_node *root);
void			run_execve(t_cmd cmd_info, char **env);

/*cmd_utils*/
void			make_cmd_info(t_cmd *cmd_info, t_tree_node *node);

/*std_utils*/
void			unlink_tmpfile(t_tree_node *node, int depth);
void			store_std_fd(int *o_fd);
void			recover_std_fd(int *o_fd);

/*exit_utils*/
void			exit_record_status(void);
void			check_signal_status(pid_t exe_fork);
void			wait_record_status(pid_t pro);
void			wait_last_command(pid_t c_pro);

/*				signal_dir				*/
/*blocking signal*/
void			set_blocking_signal(void);

/*heredoc signal*/
void			set_heredoc_signal(void);

/*shell_signal*/
void			ctrl_c(int signum);
void			set_default_signal(void);
void			set_shell_signal(void);
void			set_ign_signal(void);
int				shell_ctrl_d(void);

/*terminal option*/
void			set_terminal_print_on(void);
void			set_terminal_print_off(void);

/*wild_card*/
char			**get_file_by_wild_card(t_str_info	*str_info);
int				check_wild_card_pattern(t_str_info *str_info, int *bit_mask);
int				check_is_right_wild_card_pattern(char *str, char *file, \
t_str_info *str_info, int i);
DIR				*run_opendir(void);

/*heredoc*/
int				get_heredoc(t_tree_node *node, char **env);
char			*generate_temp_filename(char *mode);

#endif
