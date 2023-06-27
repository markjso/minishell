/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:30:25 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/20 18:26:35 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program g_program;

char	*get_location(char *cmd)
{
	char	**path_tokens;
	char	*path;
	char	*location;
	int		i;

	path = getenv("PATH");
   	//split into directories
	path_tokens = ft_split(path, ':');
	i = 0;
	while (path_tokens[i])
	{
		//append "/" to the directory
		location = ft_strjoin(path_tokens[i], "/");
        //append the command name 
		location = ft_strjoin(location, cmd);
        //check if the command exists and if it does return it
		if (access(location, F_OK) == 0)
		{
			ft_free_array(path_tokens);
			return (location);
		}
		free(location);
		i++;
	}
	ft_free_array(path_tokens);
	return (NULL);
}

void execmd(t_program *program)
{
    debugFunctionName("EXECMD");
    pid_t pid;
    char *cmd;
    char *actual_cmd;

        pid = fork();
        if (pid < 0) {
            perror("Error: Fork failed");
        } else if (pid == 0) {
            /* execute the actual command with execve */
            cmd = program->token[0];
            actual_cmd = get_location(cmd);
            if (actual_cmd == NULL) {
                printf("%s: command not found\n", cmd);
                g_program.exit_status = 1;
                printf("%d\n", g_program.exit_status);
                exit(1);
            }
            if (execve(actual_cmd, program->token, NULL) == -1) {
                perror("Error:");
                exit(1);
            }
        } else {
            wait(NULL);
            return;
        }
}