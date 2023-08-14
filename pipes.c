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
	// debugFunctionName("EXEC_PIPE");
	char		**paths;
	char		*exec_path;
    // char		*cmds;
	// t_cmd_token	*curr;
	// t_cmd_token	*temp;
    // int status;

	// temp = curr;
	// for (int z = 0; temp->data[z]; z++)
	// 	fprintf(stderr, "ERROR: temp->data : %s\n", temp->data[z]);

	paths = get_full_path();
	exec_path = get_path_for_cmd(paths, curr->name);
	fprintf(stderr, "exepath: %s\n", exec_path);
	if (exec_path)
	{
		fprintf(stderr, "exec_path: %s\n", exec_path);
		// ll_cmd_remove_node(root, curr);
		// fprintf(stderr, "temp node : %s\n", temp->data);

		for (int z = 0; curr->data[z]; z++){
			fprintf(stderr, "Just before execve temp->data[%d]: %s\n", z, curr->data[z]);}
		execve(exec_path, curr->data, g_program.envp);
		perror("execve");
		return (EXIT_FAILURE);
	}
	// waitpid(g_program.pid, &status, 0);
	// if (WIFEXITED(status))
	// {
	// 	g_program.exit_status = WEXITSTATUS(status);
	// 	ft_free_array(g_program.commands);
	// }
	return(EXIT_SUCCESS); // Ensure the child process exits after executing the command.
}

void do_pipe(t_cmd_token **root, t_cmd_token *curr)
{
    debugFunctionName("DO_PIPE");
    int			pipe1[2];
	pid_t		pid;
	int			status;

    if (pipe(pipe1) == -1)
	{
		perror("bad pipe");
		ft_exit_cmd_ll(1, root);
	}
    pid = fork();
	if (pid)
	{
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		wait(&status);
		if (WEXITSTATUS(status) != EXIT_SUCCESS)
			fprintf(stderr, "Failed\n");
	}
	else
	{
		close(pipe1[0]);
		dup2(pipe1[1], 1);
		if (exepipe(curr) == EXIT_FAILURE)
			ft_exit_cmd_ll(EXIT_FAILURE, root);
		else
			ft_exit_cmd_ll(EXIT_SUCCESS, root);
	}
}




void    set_commands(t_cmd_token **root)
{
    debugFunctionName("SET_COMMANDS");
	t_cmd_token	*new_cmd_node;
	static int	j;

	if (!j)
		j = 0;
	// for (int z = 0; g_program.token[z]; z++){
	// 	printf("value: %s\t", g_program.token[z]);}
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
	t_cmd_token	*cmd_root;
	t_cmd_token	*curr;

	cmd_root = NULL;
	debugFunctionName("HANDLE_PIPE");
    int i = 0;
    printf("this is the token: %s\n", g_program.token[i]);
	if (!g_program.token[i])
		ft_exit(51);
	set_commands(&cmd_root);
	curr = cmd_root;
    // while (g_program.token[i])
    // {
    //     if (ft_strcmp("|", g_program.token[i]) == 0) // or end of line?
    //     {
    //         execute_commands(&cmd_root);
	// 		// i = -1;
	// 	}
	// 	i++;
	// }
	while (curr)
	{
		do_pipe(&cmd_root, curr);
		curr = curr->next;
	}
	// g_program.commands = g_program.token;
	// last_command();
}
