/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:32:38 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/20 18:27:52 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "libft.h"
# include <errno.h>

# define MAXCOM 1000 // max number of letters to be supported
# define MAXLIST 100 // max number of commands to be supported

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
    // Other fields related to the shell's configuration and data
} 	t_program;

typedef struct s_envar
{
	char			*name;
	char			*value;
	struct s_envar	*next;
}	t_envar;

t_program g_program; // Global variable

int		takeInput(char *str);
void	init_global(void);
char	*get_location(char *cmd);
void	process_input(char *str, t_program *program);
void	execmd(t_program *program);
void	do_builtins(char **builtin_id, t_program *program);
int 	is_builtin_cmd(t_program *program);
void	parse_input(char *str, t_program *program);
char	*ft_strcpy(char *s1, char *s2);
void	ft_free_array(char **arr);
void	sig_initialiser(void);
int		ft_stdout(char *command, char *out_file);
int		cd_command(char **token);
int		ft_strcmp(char *s1, char *s2);
t_envar	*split_env_var(char **envp);
t_envar	*find_env_var(char *name);
t_envar	*init_env(char *name, char *value);
void	add_env_var(t_envar *node);
void	remove_env_var(char *name);
void	print_env(void);
int		export_cmd(char **token);
void	echo_cmd(char **token);
void	printpwd(void);
void	debugFunctionName(char* function_name);
int		ft_alnum_word_len(char *str, int start);
int		ft_is_not_white_space(int c);
int		ft_is_quote(int c);
void    expand_tokens(t_program *program);
int		ft_is_special_char(char *s1);
int 	ft_is_white_space(int c);
int		ft_not_whitespace_not_quote(int c);
int		ft_is_not_quote(int c);
int		ft_env_word_len(char *str);

void    ll_insert_end(t_token_list **root, t_token_list *new_node);
void    ll_insert_beginning(t_token_list **root, t_token_list *new_node);
void    ll_insert_after(t_token_list *this_node, t_token_list *new_node);
void	ll_insert_before(t_token_list **root, t_token_list *this_node, t_token_list *new_node);
void    ll_remove_node(t_token_list **root, t_token_list *this_node);
void    ll_deallocate(t_token_list **root);
t_token_list    *make_new_node(char *value);



#endif