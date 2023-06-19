/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:32:38 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/17 12:38:57 by jmarks           ###   ########.fr       */
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

typedef struct s_envar
{
	char			*name;
	char			*value;
	struct s_envar	*next;
}	t_envar;

typedef struct s_char_list
{
	int					index;
	int					type;
	int					amount;
	struct s_char_list	*next;
}	t_char_list;

int		takeInput(char *str);
char	*get_location(char *cmd);
void	execmd(char **argv);
int		builtins(char **token);
// int 	child_builtins(int builtin_id, char **token);
// int 	parent_builtins(int builtin_id, char **token);
void	parse_input(char *str, char **token);
int		process_input(char *str, char **token);
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
void	debugFunctionName(char* function_name);
int		ft_alnum_word_len(char *str, int start);
int		ft_is_not_white_space(int c);

t_char_list	*char_list_new_node(int index, char type);
void	char_list_insert_end(t_char_list **root, int index, char type);
void	char_list_delete(t_char_list **root);

#endif
