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


void exepipe(t_cmd_token *curr, int cmd_number)
{
	debugFunctionName("EXEC_PIPE");
	// char		**paths;
	char		*exec_path;
	pid_t		pid;
	int			status;

	exec_path = get_path_for_cmd(get_full_path(), curr->name);
	pid = fork();
	if (pid < 0)
	{
		perror("exepipe failed to fork");
		ft_exit(EXIT_FAILURE);
	}
	fprintf(stderr, "pid is: %d\n", pid);
	if (pid == 0)
	{
		if (curr->next != NULL)
			dup2(curr->fd_out, STDOUT_FILENO);
		if (cmd_number > 0)
			dup2(curr->fd_in, STDIN_FILENO);
		if (curr->next == NULL)
			close(curr->fd_out);
		fprintf(stderr, "execve: %s %s\n", exec_path, curr->name);
		fprintf(stderr, "fd_in: %d\n", curr->fd_in);
		fprintf(stderr, "fd_out: %d\n", curr->fd_out);
		execve(exec_path, curr->data, g_program.envp);
		perror("execve");
		exit (EXIT_FAILURE);
	}
	// Parent below
	close(curr->fd_out);
	wait(&status);
	g_program.exit_status = WEXITSTATUS(status);
	close(curr->fd_in);
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

int	init_pipes(int pipes[2][2])
{
	if (pipe(pipes[0]) == -1 || pipe(pipes[1]) == -1)
	{
		perror("Pipe failed");
		ft_exit(1);
	}
	return (0);
}

int	update_pipes(int i, int pipes[2][2])
{
	// first time run, i will be 1. Reopen pipe 0
	if (pipe(pipes[i % 1]) == -1)
	{
		perror("Pipe failed");
		exit(1);
	}
	return (i);
}

void handle_pipe()
{
    t_cmd_token *cmd_root;
    t_cmd_token *curr;
	int			pipes[2][2];
	int			i;

    debugFunctionName("HANDLE_PIPE");
    cmd_root = NULL;

    set_commands(&cmd_root);
    curr = cmd_root;

	i = init_pipes(pipes);
	fprintf(stderr, "Pipe_Number: %d\n", i);
	while (curr)
	{
		if (curr->next)
		{
			curr->fd_out = pipes[i % 2][1];
			curr->next->fd_in = pipes[i % 2][0];
		}
		// Execute the command using execve
        exepipe(curr, i);
		close(pipes[i % 2][0]);
		i = update_pipes(++i, pipes);
		curr = curr->next;
	}
	close(pipes[i % 2][0]);
	if (i > 0)
		close(pipes[(i + 1) % 2][1]);
	ll_cmd_deallocate(&cmd_root);
}
