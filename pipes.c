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
		execve(exec_path, curr->data, g_program.envp);
		perror("execve");
		exit (EXIT_FAILURE);
	}
	// Parent below
	close(curr->fd_out);
	waitpid(pid, &status, WUNTRACED);
	g_program.exit_status = WEXITSTATUS(status);
	// close(curr->fd_in);
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


void do_pipe(char *exec_path, t_cmd_token *curr)
{
    debugFunctionName("DO_PIPE");

    int pipe1[2];
	pid_t	pid;
	int status;

    if (pipe(pipe1) == -1)
	{
		perror("bad pipe");
		exit(1);
	}
    pid = fork();
	if (pid)
	{
		printf("Parent: pipe1[0]: %d\t and pipe1[1]: %d\n", pipe1[0], pipe1[1]);
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		close(pipe1[0]);
		wait(&status);
		if (WEXITSTATUS(status) != EXIT_SUCCESS)
			printf("Failed\n");
	}
	else // Child
	{
		close(pipe1[0]);
		if (curr->next != NULL)
			dup2(pipe1[1], 1); // stdoutput to parent as pipe
		close(pipe1[1]);
		execve(exec_path, curr->data, g_program.envp);
		perror("execve");
		ft_exit(EXIT_FAILURE);
	}
}

void handle_pipe()
{
    t_cmd_token *cmd_root;
    t_cmd_token *curr;
	t_cmd_token *temp;
	char		*exec_path;
	int			backup[2];
    debugFunctionName("HANDLE_PIPE");
    cmd_root = NULL;

    set_commands(&cmd_root);
    curr = cmd_root;
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	while (curr)
	{
		exec_path = get_path_for_cmd(get_full_path(), curr->name);
        do_pipe(exec_path, curr);
		temp = curr;
		curr = curr->next;
		ll_cmd_remove_node(&cmd_root, temp);
	}
	dup2(backup[0], 0);
	dup2(backup[1], 1);
	close(backup[0]);
	close(backup[1]);
}


