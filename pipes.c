/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:34:44 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/11 12:55:15 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_program	g_program;


// void exepipe(void)
// {
// 	debugFunctionName("EXEC_PIPE");
// 	char **paths;
// 	char *exec_path;
//     char *cmds;
//     // int status;

// 	cmds = g_program.token[0];
// 	printf("cmd %s\n", cmds);
// 	paths = get_full_path();
// 	exec_path = get_path_for_cmd(paths, cmds);
// 	if (exec_path)
// 	{
// 		printf("Path = %s\n", exec_path);
// 		for (int i = 0; g_program.commands[i]; i++)
// 		{
// 			printf("arg[%i] = %s\n", i, g_program.commands[i]);
// 			execve(exec_path, &g_program.commands[i], g_program.envp);
// 		}
// 		perror("execve"); 
// 		exit(EXIT_FAILURE); 
// 	}
// 	// waitpid(g_program.pid, &status, 0);
// 	// if (WIFEXITED(status))
// 	// {
// 	// 	g_program.exit_status = WEXITSTATUS(status);
// 	// 	ft_free_array(g_program.commands);
// 	// }
// 	exit(EXIT_SUCCESS); // Ensure the child process exits after executing the command.
// }


int exepipe(t_cmd_token *curr)
{
	debugFunctionName("EXEC_PIPE");
	char		**paths;
	char		*exec_path;

	paths = get_full_path();
	exec_path = get_path_for_cmd(paths, curr->name);
	fprintf(stderr, "exepath: %s\n", exec_path);
	if (exec_path)
	{
		fprintf(stderr, "exec_path: %s\n", exec_path);
		for (int z = 0; curr->data[z]; z++){
			fprintf(stderr, "Just before execve temp->data[%d]: q%sq\n", z, curr->data[z]);}
		execve(exec_path, curr->data, g_program.envp);
		perror("execve");
		exit (EXIT_FAILURE);
	}
	exit(EXIT_FAILURE); // Ensure the child process exits after executing the command.
}

void free_command(t_cmd_token *command)
{
    free(command->data);
    free(command);
}


void    set_commands(t_cmd_token **root)
{
    debugFunctionName("SET_COMMANDS");
	t_cmd_token	*new_cmd_node;
	static int	j;

	if (!j)
		j = 0;
	while (g_program.token[j])
	{
		new_cmd_node = ll_new_cmd_node(g_program.token, &j);
		ll_cmd_insert_end(root, new_cmd_node);
		printf("token is now: %s\n", g_program.token[j]);
	}
	ll_cmd_print_token(root);
}

void handle_pipe()
{
    t_cmd_token *cmd_root;
    t_cmd_token *current;
    int pipe_fd[2]; 
    int fd_in = STDIN_FILENO; // Default input is stdin
    int fd_out = STDOUT_FILENO; // Default output is stdout
    pid_t pid;

    cmd_root = NULL;
    debugFunctionName("HANDLE_PIPE");
    int i = 0;
    printf("this is the token: %s\n", g_program.token[i]);
    if (!g_program.token[i])
        ft_exit(51);
    set_commands(&cmd_root);
    current = cmd_root;

    // Declare and initialize pipe_fd here
    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }
    while (current != NULL)
    {
        printf("fd_in before fork: %d\n", fd_in);
        // Create a child process
        pid = fork();
        if (pid == -1)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) // Child process
        {
            printf("Child: fd_in = %d, fd_out = %d\n", fd_in, fd_out);
            // Input redirection
            if (current != cmd_root)
            {
                if (dup2(fd_in, STDIN_FILENO) == -1)
                {
                    perror("Input redirection failed");
                    exit(EXIT_FAILURE);
                }
            }
            // Output redirection
            if (current->next != NULL)
            {
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                {
                    perror("Output redirection failed");
                    exit(EXIT_FAILURE);
                }
                close(pipe_fd[0]);
                if (pipe_fd[0])
                    fprintf(stderr, "pipe_fd[0] exists as %d\n", pipe_fd[0]);
                else
                    fprintf(stderr, "pipe_fd[0] is closed\n");
                if (pipe_fd[1])
                    fprintf(stderr, "pipe_fd[1] exists as %d\n", pipe_fd[1]);
                else
                    fprintf(stderr, "pipe_fd[1] is closed\n");
            }
            else
            {
                // Last command, restore output to stdout
                if (dup2(fd_out, STDOUT_FILENO) == -1)
                {
                    perror("Output redirection restore failed");
                    exit(EXIT_FAILURE);
                }
            }
            // Execute the command using execve
            exepipe(current); // Replace this with your execve logic
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
        else // Parent process
        {
            printf("Parent: fd_in = %d, fd_out = %d\n", fd_in, fd_out);
            // Close the previous command's output if not stdout
            if (fd_out != STDOUT_FILENO)
            {
                close(fd_out);
            }
            // Set the current command's output as input for the next command
            if (current->next != NULL)
            {
                fd_in = pipe_fd[0];
            }       
            // Update fd_out for the next iteration
            fd_out = pipe_fd[1];
            // Wait for the child process to finish
            waitpid(pid, NULL, 0);
            current = current->next;
        }
    }
    // Close the last pipe file descriptor after the loop
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    fprintf(stderr, "pid is: %d\n", pid);
    if (pipe_fd[0])
        fprintf(stderr, "last pipe_fd[0] exists as %d\n", pipe_fd[0]);
    else
        fprintf(stderr, "last pipe_fd[0] is closed\n");
    if (pipe_fd[1])
        fprintf(stderr, "last pipe_fd[1] exists as %d\n", pipe_fd[1]);
    else
        fprintf(stderr, "last pipe_fd[1] is closed\n");

    t_cmd_token *current_cmd = cmd_root;
    while (current_cmd != NULL)
    {
        t_cmd_token *next = current_cmd->next;
        free_command(current_cmd);
        current_cmd = next;
    }
    return;
}

