/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:00:49 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/17 18:00:09 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	g_program;

int	std_output(t_program *program)
{
	debugFunctionName("STD_OUT");
	int		fd;
	char	*file;
	pid_t	pid;

	pid = fork();
	file = g_program.redirect_file;
	if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("Error: \n");
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		remove_redirect(">");
		execmd(program);
		exit (0);
	}
	else
	{
		//Parent process
		wait(NULL); // Wait for the child process to complete
        // Cleanup and restore standard output if necessary
    }
	// exit(g_program.exit_status);
	return (0);
}

int	std_input(t_program *program)
{
	debugFunctionName("STD_IN");
	int		fd;
	char	*file;
	pid_t	pid;

	pid = fork();
	file = g_program.redirect_file;
	if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			perror("Error in std_input: \n");
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		remove_redirect("<");
		execmd(program);
		exit(0);
	}
	else
	{
        // Parent process
        wait(NULL); // Wait for the child process to complete
        // Cleanup and restore standard input if necessary
    }
    return (0);
}

int	output_append(t_program *program)
{
	debugFunctionName("STD_APPEND");
	int		fd;
	char	*file;
	pid_t	pid;
		
	pid	= fork();
	file = g_program.redirect_file;

	if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND , 0644);
	if (fd < 0)
	{
		perror("Error: \n");
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	remove_redirect(">>");
	execmd(program);
	exit(0);
	}
	else
	{
        // Parent process
        wait(NULL); // Wait for the child process to complete
        // Cleanup and restore standard input if necessary
    }
	return (0);
}

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

int	check_for_redirect(t_program *program, char *str)
{
    debugFunctionName("CHECK_REDIR");
	while (str[g_program.redirect_index] != '\0')
	{
		if (ft_is_quote(str[g_program.redirect_index] == 1))
		{
			locate_second_quote(str);
			continue ;
		}
		if (str[g_program.redirect_index] == '>' && str[g_program.redirect_index + 1] == '>')
		{
			program->is_redirect = 2;
			return (2);
		}
		else if (str[g_program.redirect_index] == '>')
		{
			program->is_redirect = 1;
			return (1);
		}
		else if (str[g_program.redirect_index] == '<' && str[g_program.redirect_index + 1] == '<')
		{
			program->is_redirect = 4;
			return (4);
		}
		else if (str[g_program.redirect_index] == '<')
		{
			program->is_redirect = 3;
			return (3);
		}
		else if (str[g_program.redirect_index] == '|')
    	{
        	program->is_redirect = 5;
        	return (5);
    	}
        (g_program.redirect_index)++;
    }
    return (0); // No redirect symbol found
}

void	do_redirect(t_program *program, char *str)
{
    debugFunctionName("DO_REDIR");
	char	*file_name;
	
	if (g_program.redirect_index >= 0)
    {
		file_name = get_file_name(str);
		program->redirect_file = ft_strdup(file_name);
		free(file_name);

        if (program->is_redirect == 1)
            std_output(program);
		else if (program->is_redirect == 2)
            output_append(program);
        else if (program->is_redirect == 3)
            std_input(program);
		else if (program->is_redirect == 4)
            input_heredoc(program->redirect_file);
		else if (program->is_redirect == 5)
			handle_pipe(str);
	}
	else
	{
		error_message("Not a redirect", 1);
	}
}