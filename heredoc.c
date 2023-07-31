/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:26:32 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/19 15:26:36 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	g_program;

void	get_heredoc(int pipefd[2], char *delimiter)
{
    char *curr_line;
    pid_t pid;

	curr_line = NULL;
    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        exit(2);
    }
    pid = fork();
    if (pid == 0) // CHILD PROCESS
	{
		close(pipefd[0]); // Close read end in child process so that it will write
        while (1) // start a loop to read input from user
		{
            curr_line = readline("heredoc> "); //displays the prompt heredoc> and stores it in curr_line
            if (ft_strcmp(curr_line, delimiter) == 0) // checks to see if the delimiter is the line and if so breaks
			{
				break;
            }
            write(pipefd[1], curr_line, ft_strlen(curr_line)); // write curr_line to the write end of the pipe
			write(pipefd[1], "\n", 1);
			free(curr_line);
		}
		free(curr_line);
		close(pipefd[1]); // close the write end of the pipe in the child process. Ends writing to the pipe.
        exit(EXIT_SUCCESS); // child process ends
    }
}

void	do_heredoc(int pipefd[2])
{
	char	buffer[MAX_BUFFER]; // store the data read from the pipe
    ssize_t	nBytes; // store the number of bytes read from the pipe
	pid_t	pid;

	pid = 0;
    close(pipefd[1]); // Close write end in parent process. The parenet will only read
    waitpid(pid, NULL, 0); // wait for the child process to finish. May not be used.
	nBytes = read(pipefd[0], buffer, sizeof(buffer) - 1); // reads data from the read end into buffer
	close(pipefd[0]); // closes the read end
    if (nBytes > 0)
	{
		buffer[nBytes] = '\0';
		printf("%s", buffer); // prints the contents of buffer to the console
    }
}

int	input_heredoc(char *delimiter)
{
	int	pipefd[2];

	get_heredoc(pipefd, delimiter);
	do_heredoc(pipefd);
	return (0);
}
