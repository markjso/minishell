/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:32:38 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/22 13:43:35 by jmarks           ###   ########.fr       */
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

# define MAXCOM 5000 
# define MAXLIST 100
# define MAX_BUFFER 4096
# define T_DEFAULT	"\033[0m"

typedef struct s_token
{
	char			*data;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd_token
{
	char				*name;
	char				**data;
	int					fd_in;
	int					fd_out;
	struct s_cmd_token	*next;
}	t_cmd_token;

typedef struct s_program
{
	struct s_envar	*envar;
	char			**token;
	char			**envp;
	char			*redirect_in;
	char			*redirect_out;
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

extern int	g_exit_status;

/*initialise*/
int			take_input(char *input, t_program *program);
void		init_program(t_program *program, char **envp);
t_envar		*init_env(char *name, char *value);

/*execute commands*/
void		execmd(t_program *program);
char		**get_full_path(t_program *program);
char		*get_path_for_cmd(char **env_paths, char const *cmd,
				t_program *program);

/*pipes and signals*/
void		sig_initialiser(void);
void		handle_pipe(t_program *program);
bool		has_pipe_token(t_program *program);

/*process_input*/
void		process_input(char *str, t_token **root, t_program *program);
void		make_tokens(char *str, t_token **root);
int			find_token_number(t_token **root);
int			find_end(char *str);
void		remove_quotes(t_token **root);

/*builtins*/ 
int			cd_command(char **token, t_program *program);
int			export_cmd(char **token, t_program *program);
void		echo_cmd(char **token);
void		printpwd(void);
void		unset_cmd(char **token, t_program *program);
void		exit_cmd(char **token, t_program *program);

/*utils*/
int			ft_strcmp(char *s1, char *s2);

/*redirections*/
void		check_for_redirect(t_token **root, t_program *program);
int			do_redirect(t_token *curr, int num, int *flag, t_program *program);
void		remove_redirect(t_program *program);
int			input_heredoc(char *delimiter);
void		ft_continue(t_token **root, t_program *program);
void		remove_redirect_tokens(t_token **root,
				t_token *operator_node);

/*environment variables*/
t_envar		*split_env_var(char **envp);
t_envar		*find_env(t_envar *envars, char *name);
char		*get_envar(char *token);
void		add_env_var(t_envar *node, t_program *program);
void		remove_env_var(char *name, t_program *program);
void		print_env(t_program *program);
void		rebuild_envp(t_program *program);

/*expand variables*/
void		expand_variables(t_token **root, t_program *program);
char		*expand_dollar(char *variable, t_program *program);
int			count_dollars(char *str);
void		skip_single_quote(char *src, int *end);

/*string_utils*/
int			ft_is_not_white_space(int c);
int			ft_white_space(int c);
int			ft_is_quote(int c);
int			ft_is_not_quote(int c);
int			ft_env_word_len(char *str);
void		copy_into_array(t_token **root, t_program *program);

/*tokens*/
t_token		*make_new_node(char *value);
void		ll_insert_end(t_token **root, t_token *new_node);
void		ll_remove_node(t_token **root, t_token *this_node);
void		ll_deallocate(t_token **root);
void		ll_print_token(t_token **root);
void		replace_node_data(t_token *curr, char *new_data);

/*command tokens*/
t_cmd_token	*ll_new_cmd_node(char **value, int *j);
void		ll_cmd_insert_end(t_cmd_token **root, t_cmd_token *new_node);
void		ll_cmd_remove_node(t_cmd_token **root, t_cmd_token *this_node);

/*errors and exit*/
void		error_message(char *message, int status);
void		error_and_exit(char *message, int status, t_program *program);
void		error_and_continue(char *message, char *cmd);
void		ft_exit(int exit_number);
void		ft_free(t_program *program);
void		ft_free_envp(t_program *program);
void		error_message_cmd(char *message, int status, t_program *program);

#endif
