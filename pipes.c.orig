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

int count_commands(t_cmd_token *root)
{
    int count = 0;
    t_cmd_token *current = root;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    printf("count is: %d\n", count);
    return (count);
}

void handle_pipe()
{
    t_cmd_token *cmd_root;
    t_cmd_token *current;

    cmd_root = NULL;
    debugFunctionName("HANDLE_PIPE");
    int i = 0;
    printf("this is the token: %s\n", g_program.token[i]);
    if (!g_program.token[i])
        ft_exit(51);
    set_commands(&cmd_root);
    current = cmd_root;

    int num_pipes = count_commands(cmd_root) - 1;
    int pipes[num_pipes][2];

    for (int j = 0; j < num_pipes; j++)
    {
        if (pipe(pipes[j]) == -1)
        {
            perror("Pipe creation failed");
            exit(EXIT_FAILURE);
        }
    }
    int fd_in = STDIN_FILENO;
    int fd_out = STDOUT_FILENO;
    int status;
    int cmd_index = 0; // Counter for the current command index

    while (current != NULL)
    {
        printf("fd_in before fork: %d\n", fd_in);
        // Create a child process
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) // Child process
        {
            printf("Child: fd_in = %d, fd_out = %d\n", fd_in, fd_out);
            // Input redirection
            if (fd_in != STDIN_FILENO)
            {
                if (dup2(pipes[cmd_index][PIPE_WRITE], STDOUT_FILENO) == -1)
                {
                    perror("Input redirection failed");
                    exit(EXIT_FAILURE);
                }
               close(pipes[cmd_index][PIPE_READ]);
               close(pipes[cmd_index][PIPE_WRITE]);
            }
            // Output redirection
            if (current->next != NULL)//not the last command
            {
                if (dup2(pipes[cmd_index][PIPE_READ], STDIN_FILENO) == -1)
                {
                    perror("Output redirection failed");
                    exit(EXIT_FAILURE);
                }
                close(pipes[cmd_index][PIPE_WRITE]);
            }
            else
            {
            //     if (dup2(pipes[cmd_index][PIPE_WRITE], STDOUT_FILENO) == -1)
            //     {
            //         perror("Output redirection failed");
            //         exit(EXIT_FAILURE);
            //     }
                close(pipes[cmd_index][PIPE_READ]);
            }
            // Execute the command using execve
            exepipe(current);
        }
        else // Parent process
        {
            printf("Parent: fd_in = %d, fd_out = %d\n", fd_in, fd_out);
            // Close the input/output file descriptors if not stdin/stdout
            if (fd_in != STDIN_FILENO)
            {
                close(fd_in);
            }
            if (current->next != NULL)
            {
                close(pipes[cmd_index][PIPE_WRITE]);
            }
            else if (fd_out != STDOUT_FILENO)
            {
                close(fd_out);
            }
            // Wait for the child process to finish
            waitpid(pid, &status, 0);
            current = current->next;
            cmd_index++; // Increment the current command index
        }
    }
    for (int j = 0; j < num_pipes; j++)
    {
        close(pipes[j][PIPE_READ]);
        close(pipes[j][PIPE_WRITE]);
    }

    t_cmd_token *current_cmd = cmd_root;
    while (current_cmd != NULL)
    {
        t_cmd_token *next = current_cmd->next;
        free_command(current_cmd);
        current_cmd = next;
    }

    return;
}
