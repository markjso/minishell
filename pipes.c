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
	debugFunctionName("CLOSE_PIPE");
	int	is_first_command;
	int	pipefd[2];
	int	status;

	is_first_command = 1;
	if (!is_first_command)
		close(pipefd[0]);
	if (str != NULL)
		close(pipefd[1]);
	waitpid(g_program.pid, &g_program.exit_status, 0);
	if (WIFEXITED(status))
		g_program.exit_status = WEXITSTATUS(status);
}

/*tokenises the input string "str" based on the delimiter "|"
trims each command of any whitespace and creates the pipe for 
communication between commands if the string contains more than
one command*/
// void	handle_pipe(char *str)
// {
// 	debugFunctionName("HANDLE_PIPE");
//     char	*token; //store tokens extracted from str
// 	char	*end; //trim whitespaces
//     int		is_first_command; //flag to indicate if the current command is the first one
//     int		pipefd[2]; //pipe file descriptors

// 	is_first_command = 1;
// 	token = ft_strtok_r(&str, "|");
// 	//while loop to tokenise the input str using the delimiter "|". Allows for 
// 	//multiple commands separated by pipes
//     while (token) 
// 	{
//         //Trim leading whitespace from the token.
//         while (*token == ' ' || *token == '\t')
//             token++;
//         end = token + ft_strlen(token) - 1;//sets the end ptr to the last character of the token
//         //trim trailing whitespace from the token
// 		while (end > token && (*end == ' ' || *end == '\t'))
//             end--;
// 		//null terminate the token	
//         *(end + 1) = '\0';
//         //Create a pipe if it's not the first command
//         if (!is_first_command)
// 		{
//             if (pipe(pipefd) == -1)
//                 perror("Error");
//         }
// 		is_first_command = 0;
// 		token = ft_strtok_r(&str, "|");
// 	}
// }

//executes the indiviudal commands separated by "|"
void do_pipe(t_token_list **root)
{
    debugFunctionName("DO_PIPE");
    int is_first_command = 1;
    int pipefd[2];
    int saved_stdout = dup(STDOUT_FILENO);

    t_token_list *curr = *root;
    pid_t pid;

    while (curr)
    {
        if (pipe(pipefd) == -1)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid < 0)
        {
            perror("Error");
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
                    perror("Error");
                    exit(EXIT_FAILURE);
                }
            }

            // Close the unused write end of the pipe
            close(pipefd[1]);

            // Execute the command
            execmd(&g_program);

            // Exit the child process
            exit(EXIT_SUCCESS);
        }
        else
        {
            // Parent process
            if (!is_first_command)
            {
                close(pipefd[0]); // Close the unused read end of the pipe
            }

            // Wait for the child process to finish
            waitpid(pid, NULL, 0);

            // Restore stdout to the original file descriptor
            dup2(saved_stdout, STDOUT_FILENO);

            curr = curr->next;
            is_first_command = 0;
        }
    }
}
