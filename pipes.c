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

void setup_pipes(int *current_pipe, int *next_pipe) {
    if (current_pipe[0] != -1) {
        close(current_pipe[0]); // Close the read end of the current pipe
        close(current_pipe[1]); // Close the write end of the current pipe
    }

    if (next_pipe[0] != -1) {
        current_pipe[0] = next_pipe[0]; // Update read end with the next pipe's read end
        current_pipe[1] = next_pipe[1]; // Update write end with the next pipe's write end
    }
}

void exit_pipe(t_token_list *current)
{
    debugFunctionName("CLOSE_PIPE");
    int pipe_fd[2];
    if (current->next) 
    {
        close(g_program.pipe_fd[0]);
        g_program.pipe_fd[0] = pipe_fd[0];
        g_program.pipe_fd[1] = pipe_fd[1];
    }
    waitpid(g_program.pid, &g_program.exit_status, 0);
}

/*tokenises the input string "str" based on the delimiter "|"
trims each command of any whitespace and creates the pipe for 
communication between commands if the string contains more than
one command*/
void handle_pipe(t_token_list *current) 
{
    debugFunctionName("HANDLE_PIPE");
    // t_token_list *curr = root;
    int is_first_command = 1;

    while (current != NULL)
    {
        if (current->data[0] == '|') 
        {
            if (!is_first_command)
            {
                close(g_program.pipe_fd[1]);
            }
            if (pipe(g_program.pipe_fd) == -1)
            {
                perror("Error creating pipe");
            }
            is_first_command = 0;
            current = current->next;
        } else
        {
            // Only execute the first command
            do_pipe(current);
            if (current->next && current->next->data[0] == '|')
            {
                current = current->next->next; // Skip the pipe symbol '|'
            }
            else
            {
                current = current->next;
            }
        }
    }
}

void reset_pipe_state() {
    g_program.pipe_fd[0] = -1;
    g_program.pipe_fd[1] = -1;
    g_program.is_first_command = 1;
}

char **split_command(const char *command)
{
    debugFunctionName("SPLIT_CMDS");
    char **tokens = malloc(MAXARGS * sizeof(char *));
    char *token;
    int i = 0;

    token = strtok(ft_strdup(command), " "); // Split the command using spaces as delimiters
    while (token != NULL)
    {
        tokens[i++] = ft_strdup(token);
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;

    return tokens;
}

void do_pipe(t_token_list *current)
{
    debugFunctionName("DO_PIPE");
    int is_first_command = 1;

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("Error creating pipe");
    }
    g_program.pid = fork();
    if (g_program.pid < 0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    if (g_program.pid == 0)
    {
        // Child process
        if (!is_first_command)
        {
            close(g_program.pipe_fd[1]);
            if (dup2(g_program.pipe_fd[0], STDIN_FILENO) < 0)
            {
                perror("Error");
                exit(EXIT_FAILURE);
            }
            close(g_program.pipe_fd[0]);
        }
        if (current->next != NULL)
        {
            close(pipe_fd[0]);
            if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
            {
                perror("Error");
                exit(EXIT_FAILURE);
            }
            close(pipe_fd[1]);
        }
        // Execute the command
        char **command_tokens = split_command(current->data);
        execvp(command_tokens[0], command_tokens);
    }
    else
    {
        // Parent process
        exit_pipe(current);
    }
}