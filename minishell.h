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
# include "leaks.h"

# define MAXCOM 5000 // max number of letters to be supported
# define MAXLIST 100 // max number of commands to be supported
# define MAX_BUFFER 4096
# define MAXARGS 20
# define T_DEFAULT	"\033[0m"

/*Struct for holding tokenised user input.*/
typedef struct s_token
{
	char			*data;
	struct s_token	*next;
}	t_token;

typedef struct s_program
{
	struct s_envar	*envar;
	char			**token;
	char			**envp;
	char			**commands;
	char			*prompt;
	int				exit_status;
	char			*redirect_file;
	char			*redirect_in;
	char			*redirect_out;
	int				is_redirect;
	int				redirect_index;
	int				out_file;
	int				out_backup;
	int				in_file;
	int				in_backup;
	int				redir_out_flag;
	int				redir_in_flag;
}	t_program;

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

/*execute commands*/
void	execmd(void);
char	**get_full_path(void);
char	*get_path_for_cmd(char **env_paths, char const *cmd);

/*pipes and signals*/
void	sig_initialiser(void);
void	handle_pipe(void);
bool	has_pipe_token(void);
char	**split_command(const char *command);
void	execute_commands(void);

/*process_input*/
void	process_input(char *str, t_token **root);
void	make_tokens(char *str, t_token **root);
int		find_token_number(t_token **root);
int		find_end(char *str);
void	remove_quotes(t_token **root);

/*builtins*/ 
int		cd_command(char **token);
int		export_cmd(char **token);
void	echo_cmd(char **token);
void	printpwd(void);
void	unset_cmd(char **token);
void	exit_cmd(char **token);

/*utils*/
int		ft_is_special_char(char *s1);
char	*ft_strcpy(char *s1, char *s2);
void	ft_free_array(char **arr);
int		ft_strcmp(char *s1, char *s2);

/*redirections*/
void	check_for_redirect(t_token **root);
void	do_redirect(t_token *curr, int num, int *flag);
void	remove_redirect(void);
int		input_heredoc(char *delimiter);
char	*get_file_name(char *str);
void	locate_second_quote(char *str);
void	ft_continue(t_token **root);
void	remove_redirect_tokens(t_token **root,
			t_token *operator_node);

/*environment variables*/
t_envar	*split_env_var(char **envp);
t_envar	*find_env(t_envar *envars, char *name);
char	*get_envar(char *token);
void	add_env_var(t_envar *node);
void	remove_env_var(char *name);
void	print_env(void);
int		count_envars(t_envar *envars);
void	rebuild_envp(void);

/*expand variables*/
void	expand_variables(t_token **root);
char	*expand_dollar(char *variable);
int		env_len(char *str);
char	*return_string(char *src, int terminator);
void	skip_single_quote(char *src, int *end);

/*string_utils*/
int		ft_alnum_word_len(char *str, int start);
int		ft_is_valid_var_char(char c);
int		ft_env_word_len(char *str);
int		ft_is_not_white_space(int c);
int		ft_white_space(int c);
int		ft_is_quote(int c);
int		ft_is_not_quote(int c);
int		ft_env_word_len(char *str);
void	remove_redirect(void);
void	copy_into_array(t_token **root);
int		ft_not_whitespace_not_quote(int c);

/*tokens*/
t_token	*make_new_node(char *value);
void	ll_insert_end(t_token **root, t_token *new_node);
void	ll_insert_beginning(t_token **root, t_token *new_node);
void	ll_insert_after(t_token *this_node, t_token *new_node);
void	ll_insert_before(t_token **root, t_token *this_node, t_token *new_node);
void	ll_remove_node(t_token **root, t_token *this_node);
void	ll_deallocate(t_token **root);
void	ll_print_token(t_token **root);
void	replace_node_data(t_token *curr, char *new_data);

/*errors and exit*/
void	error_message(char *message, int status);
void	error_and_exit(char *message, int status);
void	ft_exit(int exit_number);
void	ft_free_envp(void);
void	error_message_cmd(char *message, int status);
void	debugFunctionName(char *function_name);

#endif
