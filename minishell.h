/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:32:38 by jmarks            #+#    #+#             */
/*   Updated: 2023/04/12 14:32:45 by jmarks           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

int takeInput(char *str);
char	*find_cmd_path(char *cmd, char **path);
void	execute_cmd(char *cmd, char **envp);
char	**get_path(char **envp);
int builtins(char** token);
void execArgs(char** token);
void parse_input(char* str, char** token);
int process_input(char* str, char** token);

#endif
