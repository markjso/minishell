/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:34:44 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/28 22:03:46 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_program	g_program;



void exepipe(void)
{
	debugFunctionName("EXEC_PIPE");
	char **paths;
	char *exec_path;
    char *cmds;
    int status;

	cmds = g_program.commands[0];
	paths = get_full_path();
	exec_path = get_path_for_cmd(paths, &cmds[0]);
	if (exec_path)
	{
		execve(exec_path, g_program.commands, g_program.envp);
		perror("execve"); 
		exit(EXIT_FAILURE); 
	}
	// waitpid(g_program.pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_program.exit_status = WEXITSTATUS(status);
	}
	exit(EXIT_SUCCESS); // Ensure the child process exits after executing the command.
}

void last_command(void)
{
	debugFunctionName("LAST_CMD");
	int status;

	waitpid(g_program.pid, &status, 0);
	if (WIFEXITED(status))
		g_program.exit_status = WEXITSTATUS(status);
		ft_free_array(g_program.token);
}

void	set_commands()
{
    debugFunctionName("SET_CMDS");
    char **tokens;
    int i;
	int j;

    i = 0; 
	tokens = &g_program.token[i];
	while (tokens[i] && ft_strcmp("|", tokens[i])) // while exist and not |
		i++;
	if (!tokens[i]) // if end of **
        g_program.commands = tokens;
	else // if not the ned
	{
		g_program.commands = malloc(sizeof(*g_program.commands) * (i + 1));
		j = 0;
		while (j < i)
		{
			g_program.commands[j] = tokens[j];
			j++;
		}
		g_program.commands[i] = NULL;
	}
}


void handle_pipe(void) 
{
    debugFunctionName("HANDLE_PIPE");
    int i = 0;
    printf("this is the token: %s\n", g_program.token[i]);
	if (!g_program.token[i])
		exit (0);
    while (g_program.token[i])
    {
        if (!ft_strcmp("|", g_program.token[i])) 
        {
            execute_commands(g_program.token);
			i = -1;
		}
		i++;
	}
	printf("do we get to here?\n");
	g_program.commands = g_program.token;
	last_command();
}


void	set_pipes(void)
{
	int	pid;
	int	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid != 0) // parent
	{
		if(!g_program.pid)
			g_program.pid = pid;
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	else if (pid == 0) // child
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exepipe();
	}
}



void	do_pipe(void)
{
    debugFunctionName("DO_PIPE");
	set_commands();
	set_pipes();
}