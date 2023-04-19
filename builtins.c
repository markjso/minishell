/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:55:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/04/18 13:55:07 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execArgs(char **token)
{
	pid_t pid = fork();

	if (pid == -1) {
		printf("\nFailed forking child..");
		return;
	} else if (pid == 0) {
		if (execvp(token[0], token) < 0) {
			printf("Could not execute command..\n");
		}
		exit(0);
	} else {
		wait(NULL);
		return;
	}
}

void printpwd()
{
    char pwd[256];
    getcwd(pwd, sizeof(pwd));
    printf("\nDir: %s", pwd);
}

int builtins(char** token)
{
    int no_of_builtins;
    int i; 
	
    no_of_builtins = 7;
    i = 0;
    char* builtin_ID[no_of_builtins];

	builtin_ID[0] = "echo";
	builtin_ID[1] = "cd";
	builtin_ID[2] = "pwd";
	builtin_ID[3] = "export";
    builtin_ID[4] = "unset";
    builtin_ID[5] = "env";
    builtin_ID[6] = "exit";

	while (i < no_of_builtins && strcmp(token[0], builtin_ID[i]) != 0) 
    {
		i++;
    }

    if (i == 2) 
        printpwd();
    else if (i == 6)
        exit(0);

    return (0);
}

void parse_input(char* str, char** token)
{
    int i;

    i = 0;
    while (i < MAXLIST) {
        token[i] = strsep(&str, " ");

        if (token[i] == NULL) {
            break;
        }

        if (ft_strlen(token[i]) == 0) {
            i--;
        }
        i++;
    }
}

int process_input(char *str, char **token)
{
    parse_input(str, token);

    if (builtins(token))
        return (0);
    else
        return (1);
}
