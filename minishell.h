/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:32:38 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/19 13:05:20 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include "libft.h"
# include <errno.h>

# define MAXCOM 5000 // max number of letters to be supported
# define MAXLIST 100 // max number of commands to be supported
# define MAX_BUFFER 4096
# define MAXARGS 20

/*Struct for holding tokenised user input.*/
typedef struct s_token_list
{
	char				*data;
	struct s_token_list	*next;
}	t_token_list;

typedef struct s_program
{
    struct s_envar *envar;
	char	**token;
	char	**envp;
	char	*prompt;
	int		exit_status;
	pid_t			pid;
	char    *redirect_file;
	char	*redirect_in;
	char	*redirect_out;
	int		is_redirect;
	int		redirect_index;
	int		out_file;
	int		out_backup;
	int		in_file;
	int		in_backup;
	int		redir_out_flag;
	int		redir_in_flag;
	int 	pipe_fd[2];
	int		is_first_command;
    // Other fields related to the shell's configuration and data
} 	t_program;

typedef struct s_envar
{
	char			*name;
	char			*value;
	struct s_envar	*next;
}	t_envar;

t_program	g_program;

/*initialise*/
int		take_input(char *input);
void	init_global(void);
t_envar	*init_env(char *name, char *value);

// char	*get_command(char *path);
void	process_input(char *str, t_token_list **root);
void	execmd(t_program *program);
t_envar	*find_env(t_envar *envars, char *name);

/*pipes and signals*/
void	do_pipe(t_token_list *current);
void	sig_initialiser(void);
char	*ft_strtok_r(char **str, char *delim);
void 	handle_pipe(t_token_list *current);
bool	has_pipe_token(char *str);
// void exe_pipe_cmd(char **command_tokens);
char	**split_command(const char *command);
void	reset_pipe_state();

/*process_input*/
void	process_input(char *str, t_token_list **root);
void	make_tokens(char *str, t_token_list **root);
int		find_token_number(t_token_list **root);
int		find_end(char *str);
void	remove_quotes(t_token_list **root);

/*builtins*/
void	do_builtins(char **builtin_id, t_program *program);
int		is_builtin_cmd();
int		cd_command(char **token);
int		export_cmd(char **token);
void	echo_cmd(char **token);
void	printpwd(void);
void	exit_cmd(char **token);

/*utils*/
int		ft_is_special_char(char *s1);
char	*ft_strcpy(char *s1, char *s2);
void	ft_free_array(char **arr);
int		ft_strcmp(char *s1, char *s2);

/*redirections*/
void	check_for_redirect(t_token_list **root);
void	do_redirect(t_token_list *curr, int num, int *flag);
void	remove_redirect();
int		input_heredoc(char *delimiter);
char	*get_file_name(char *str);
void	locate_second_quote(char *str);
void	ft_continue(t_token_list **root);

/*environment variables*/
t_envar	*split_env_var(char **envp);
t_envar	*find_env_var(char *name);
char	*get_envar(char *token);
void	add_env_var(t_envar *node);
void	remove_env_var(char *name);
void	print_env(void);
int		count_envars(t_envar *envars);
void	rebuild_envp(void);

/*expand variables*/
void	expand_variables(t_token_list **root);
char	*expand_dollar(char *variable);
int		env_len(char *str);
char	*return_string(char *src, int terminator);
void	skip_single_quote(char *src, int *end);

/*string_utils*/
int		ft_alnum_word_len(char *str, int start);
int		ft_is_valid_var_char(char c);
int		ft_env_word_len(char *str);
int		ft_is_not_white_space(int c);
int		ft_is_white_space(int c);
int		ft_is_quote(int c);
int		ft_is_not_quote(int c);
int		ft_env_word_len(char *str);
void	remove_redirect();
void	copy_into_array(t_token_list **root);
int		ft_not_whitespace_not_quote(int c);

t_token_list    *make_new_node(char *value);
void    ll_insert_end(t_token_list **root, t_token_list *new_node);
void    ll_insert_beginning(t_token_list **root, t_token_list *new_node);
void    ll_insert_after(t_token_list *this_node, t_token_list *new_node);
void	ll_insert_before(t_token_list **root, t_token_list *this_node, t_token_list *new_node);
void    ll_remove_node(t_token_list **root, t_token_list *this_node);
void    ll_deallocate(t_token_list **root);
void	ll_print_token(t_token_list **root);
void	replace_node_data(t_token_list *curr, char *new_data);

/*errors*/
void	error_message(char *message, int status);
void	error_and_exit(char *message, int status);

void	debugFunctionName(char *function_name);

#endif

// void	free_dollar_found(char **env_str, char **first, char **first_2, 
// char **last, char **last_2);
