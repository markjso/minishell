/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:00:49 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/27 15:00:51 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program g_program;

void	remove_redirect(char *redirector)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	while (g_program.token[i])
		i++;
	new = malloc(sizeof(*new) * (i - 1));
	i = 0;
	j = 0;
	while (g_program.token[i])
	{
		if (!ft_strcmp(g_program.token[i], redirector))
			i += 2;
		if (!g_program.token[i])
			break ;
		new[j++] = ft_strdup(g_program.token[i++]);
	}
	new[j] = NULL;
	ft_free_array(g_program.token);
	g_program.token = new;
}

void restore_stdout()
{
    int stdout_fd = dup(STDOUT_FILENO);  // Save the original standard output file descriptor
    dup2(stdout_fd, STDOUT_FILENO);     // Restore the standard output
    close(stdout_fd);
}

int std_output(t_program *program)
{
	debugFunctionName("STD_OUT");
	int fd;
	char *file;

	file = g_program.redirect_file;

	printf("Redirect File: %s\n", file);
    printf("Token 1: %s\n", program->token[1]);

	if (program->token[1][0] == '\0') // Check if only ">" is present
	{
		printf("Invalid command\n");
		return (-1);
	}
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error: \n");
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	remove_redirect(">");
	execmd(program);
	restore_stdout();
	return (0);
	exit(g_program.exit_status);
}

int std_input(void)
{
	debugFunctionName("STD_IN");
	int	fd;
	char *file;

	file = g_program.redirect_file;

	printf("Redirect File: %s\n", file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: \n");
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	remove_redirect("<");
	return(-1);
}

int output_append(t_program *program)
{
	debugFunctionName("STD_APPEND");
	int fd;
	char *file;

	file = g_program.redirect_file;

	printf("Redirect File: %s\n", file);
    printf("Token 1: %s\n", program->token[1]);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND , 0644);
	if (fd < 0)
	{
		perror("Error: \n");
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	// restore_stdout();
	remove_redirect(">>");
	execmd(program);
	return (0);
}

void get_heredoc(int pipefd[2], char *delimiter)
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
    if (pid == 0) // CHILD
	{ 
        close(pipefd[0]); // Close read end in child process

        while (1) 
		{
            curr_line = readline("heredoc> ");
            if (ft_strcmp(curr_line, delimiter) == 0)
			{
                break;
            }
            write(pipefd[1], curr_line, ft_strlen(curr_line));
            write(pipefd[1], "\n", 1);
            free(curr_line);
        }
        free(curr_line);
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }
}

void do_heredoc(int pipefd[2])
{
    char buffer[MAX_BUFFER];
    ssize_t nBytes;
	pid_t pid;

	pid = 0;
    close(pipefd[1]); // Close write end in parent process
    waitpid(pid, NULL, 0);

    nBytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
    close(pipefd[0]);

    if (nBytes > 0)
	{
        buffer[nBytes] = '\0';
        printf("%s", buffer);
    }
}

int input_heredoc(char *delimiter)
{
    int pipefd[2];

    get_heredoc(pipefd, delimiter);
    do_heredoc(pipefd);
    return (0);
}

int check_for_redirect(t_program *program)
{
    debugFunctionName("CHECK_REDIR");
    int i = 0;

    while (program->token[i])
    {
        if (!ft_strcmp(">", program->token[i]))
		{
            program->is_redirect = 1;
			return (i);
		}
        else if (!ft_strcmp(">>", program->token[i]))
		{
            program->is_redirect = 2;
			return (i);
		}
        else if (!ft_strcmp("<", program->token[i]))
		{
            program->is_redirect = 3;
			return (i);
		}
        else if (!ft_strcmp("<<", program->token[i]))
		{
            program->is_redirect = 4;
			return (i);
		}
        i++;
    }
    return (-1); // No redirect symbol found
}


void do_redirect(t_program *program)
{
    debugFunctionName("DO_REDIR");
    int redirect_index;

	redirect_index = check_for_redirect(program);
	printf("Redirect index: %d\n", redirect_index);
    if (redirect_index >= 0)
    {
        if (program->is_redirect == 1)
        {
            program->redirect_file = ft_strdup(program->token[redirect_index + 1]);
            std_output(program);
        }
		else if (program->is_redirect == 2)
		{
			program->redirect_file = ft_strdup(program->token[redirect_index + 1]);
            output_append(program);
		}
        else if (program->is_redirect == 3)
        {
            program->redirect_file = ft_strdup(program->token[redirect_index + 1]);
            std_input();
        }
		else if (program->is_redirect == 4)
		{
			program->redirect_file = ft_strdup(program->token[redirect_index + 1]);
            input_heredoc(program->redirect_file);
		}
    }
    else
    {
        error_message("Not a redirect", 1);
    }
}