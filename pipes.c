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

void	close_pipe(char *str)
{
	int	is_first_command;
	int	pipefd[2];

	is_first_command = 1;
	{
		if (!is_first_command)
			close(pipefd[0]);
		wait(NULL);
		return ;
		if (str != NULL)
			close(pipefd[1]);
	}
}

/*tokenises the input string "str" based on the delimiter "|"
trims each command of any whitespace and creates the pipe for 
communication between commands if the string contains more than
one command*/
void	handle_pipe(char *str)
{
	debugFunctionName("HANDLE_PIPE");
    char	*token; //store tokens extracted from str
	char	*end; //trim whitespaces
    int		is_first_command; //flag to indicate if the current command is the first one
    int		pipefd[2]; //pipe file descriptors

	is_first_command = 1;
	token = ft_strtok_r(&str, "|");
	//while loop to tokenise the input str using the delimiter "|". Allows for 
	//multiple commands separated by pipes
    while (token) 
	{
        //Trim leading whitespace from the token.
        while (*token == ' ' || *token == '\t')
            token++;
        end = token + ft_strlen(token) - 1;//sets the end ptr to the last character of the token
        //trim trailing whitespace from the token
		while (end > token && (*end == ' ' || *end == '\t'))
            end--;
		//null terminate the token	
        *(end + 1) = '\0';
        //Create a pipe if it's not the first command
        if (!is_first_command)
		{
            if (pipe(pipefd) == -1)
                error_and_exit();
        }
		is_first_command = 0;
		token = ft_strtok_r(&str, "|");
	}
}

//executes the indiviudal commands separated by "|"
void	do_pipe(t_program *program, char *str)
{
    debugFunctionName("DO_PIPE");
    int		is_first_command;
    int		pipefd[2];
	pid_t	pid;

	is_first_command = 1;
	handle_pipe(str);
	pid = fork();
	if (pid == 0)
	{
        //Child process
		if (!is_first_command)
		{
                // Redirect stdin to read from the previous pipe
				if (dup2(pipefd[0], STDIN_FILENO) == -1)
				{
                    error_and_exit();
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
		close_pipe(str);
}