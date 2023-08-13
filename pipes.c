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


void exepipe(t_cmd_token **root)
{
	// debugFunctionName("EXEC_PIPE");
	char		**paths;
	char		*exec_path;
    // char		*cmds;
	t_cmd_token	*curr;
	t_cmd_token	*temp;
    // int status;

	curr = *root;
	temp = curr;
	paths = get_full_path();
	exec_path = get_path_for_cmd(paths, temp->name);
	if (exec_path)
	{
		// printf("Path: %s\n", exec_path);
		ll_cmd_remove_node(root, curr);
		// printf("temp node : %s\n", temp->name);
		execve(exec_path, temp->data, g_program.envp);
		perror("execve"); 
		ft_exit(EXIT_FAILURE); 
	}
	// waitpid(g_program.pid, &status, 0);
	// if (WIFEXITED(status))
	// {
	// 	g_program.exit_status = WEXITSTATUS(status);
	// 	ft_free_array(g_program.commands);
	// }
	ft_exit(EXIT_SUCCESS); // Ensure the child process exits after executing the command.
}


void do_pipe(t_cmd_token **root)
{
    debugFunctionName("DO_PIPE");
    int			pipe1[2];
	pid_t		pid;
	int			status;

    if (pipe(pipe1) == -1)
	{
		perror("bad pipe");
		ft_exit(1);
	}
    pid = fork();
	if (pid == 0)
	{
		close(pipe1[0]);
		dup2(pipe1[1], 1);
		exepipe(root);
	}
	else
	{
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		wait(&status);
		waitpid(pid, NULL, WNOHANG);
		if (WEXITSTATUS(status) != EXIT_SUCCESS)
			printf("Failed\n");
	}
}




void    set_commands(t_cmd_token **root)
{
    debugFunctionName("SET_COMMANDS");
	t_cmd_token	*new_cmd_node;
	static int	j;

	if (!j)
		j = 0;
	// for (int z = 0; value[z]; z++)
	// 	printf("value: %s\t", value[z]);
	while (g_program.token[j])
	{
		new_cmd_node = ll_new_cmd_node(g_program.token, &j);
		ll_cmd_insert_end(root, new_cmd_node);
		printf("token is now: %s\n", g_program.token[j]);
	}
	ll_cmd_print_token(root);
}


// void	execute_commands(t_cmd_token **cmd_root)
// {
// 	 debugFunctionName("EXEXUTE_PIPE_COMMAND");
//     //  int	i = 0;
// 	// set_commands(cmd_root);

// 	// sig_initialiser();
// 	// printf("commmands in g_program.commands: %s\n", g_program.commands[i]);
// 	// do_pipe(cmd_root);
// 	// last_command();
// 	// execmd();
// }

void handle_pipe() 
{
	t_cmd_token	*cmd_root;

	cmd_root = NULL;
    debugFunctionName("HANDLE_PIPE");
    int i = 0;
    printf("this is the token: %s\n", g_program.token[i]);
	if (!g_program.token[i])
		ft_exit(51);
	set_commands(&cmd_root);
    // while (g_program.token[i])
    // {
    //     if (ft_strcmp("|", g_program.token[i]) == 0) // or end of line?
    //     {
    //         execute_commands(&cmd_root);
	// 		// i = -1;
	// 	}
	// 	i++;
	// }
	do_pipe(&cmd_root);
	// g_program.commands = g_program.token;
	// last_command();
}
