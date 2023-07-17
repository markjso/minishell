/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:34:44 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/11 14:36:19 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_program	g_program;

void	handle_pipe(char *str)
{
	debugFunctionName("HANDLE_PIPE");
    char	*token;
	char	*end;
    int		is_first_command;
    int		pipefd[2];

	is_first_command = 1;
    while ((token = ft_strtok_r(&str, "|"))) 
	{
        // Trim leading and trailing whitespace from the token.
        while (*token == ' ' || *token == '\t')
            token++;
        end = token + ft_strlen(token) - 1;
        while (end > token && (*end == ' ' || *end == '\t'))
            end--;
        *(end + 1) = '\0';

        // Create a pipe if it's not the first command
        if (!is_first_command)
		{
            if (pipe(pipefd) == -1)
			{
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
	}
}

void	do_pipe(t_program *program, char *str)
{
    debugFunctionName("DO_PIPE");
    int		is_first_command;
    int		pipefd[2];
	pid_t	pid;

	is_first_command = 1;
	handle_pipe(str);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
            // Child process
		if (!is_first_command)
		{
                // Redirect stdin to read from the previous pipe
				if (dup2(pipefd[0], STDIN_FILENO) == -1)
				{
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                // Close the unused write end of the pipe
                close(pipefd[1]);
		}
            // Execute the command
		execmd(program);
            // Exit the child process
		exit(EXIT_SUCCESS);
	}
	else
	{
		// Parent process
		if (!is_first_command)
		{
		   	//Close the unused read end of the pipe
			close(pipefd[0]);
		}
		// Wait for the child process to complet
		waitpid(pid, NULL, 0);
		// If not the last command, close the write end of the pipe
		if (str != NULL)
		{
			close(pipefd[1]);
		}
	}
	is_first_command = 0;
}