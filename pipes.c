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

	cmds = g_program.token[0];
	printf("cmd %s\n", cmds);
	paths = get_full_path();
	exec_path = get_path_for_cmd(paths, cmds);
	if (exec_path)
	{
		execve(exec_path, g_program.commands, g_program.envp);
		perror("execve"); 
		exit(EXIT_FAILURE); 
	}
	waitpid(g_program.pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_program.exit_status = WEXITSTATUS(status);
		ft_free_array(g_program.commands);
	}
	exit(EXIT_SUCCESS); // Ensure the child process exits after executing the command.
}

void	set_commands(void)
{
    debugFunctionName("SET_CMDS");
    char **tokens;
    int i;
	int j;

    i = 0; 
	tokens = &g_program.token[i];
	while (tokens[i] && ft_strcmp("|", tokens[i]))
		i++;
	if (!tokens[i])
    {
        g_program.commands = tokens;
    }
	else
	{
		g_program.commands = malloc(sizeof(*g_program.commands) * (i + 1));
		j = 0;
		while (j < i)
		{
			g_program.commands[j] = tokens[j];
			printf("Command %d: %s\n", j, g_program.commands[j]); 
			j++;
		}
		g_program.commands[i] = NULL;
	}
}

/*
	first cmd will be first token 
	2nd cmd will be immeditay after pipe 
*/

void do_pipe(void)
{
    debugFunctionName("DO_PIPE");

    int pipe1[2];
	pid_t	pid;
	pid_t	pid2;
	int status;
    if (pipe(pipe1) == -1)
	{
		perror("bad pipe");
		exit(1);
	}
    pid = fork();
	if (pid == 0)
	{
		dup2(pipe1[1], STDOUT_FILENO);
		close(pipe1[0]);
		close(pipe1[1]);
		printf("getting to child\n");
		exepipe();
	}
	else
	{
		pid2=fork();
		if (pid2 == 0)
		{
			dup2(pipe1[0], STDIN_FILENO);
			close(pipe1[1]);
			close(pipe1[0]);
			printf("getting to parent\n");
			exepipe();	
		}
		else
		{
			close(pipe1[0]);
			close(pipe1[1]);
			waitpid(pid2, &status, 1);
		}
		waitpid(pid, &status, 1);
	}
}


void	execute_commands(void)
{
	 debugFunctionName("EXEXUTE_PIPE_COMMAND");
    //  int	i = 0;

	sig_initialiser();
	set_commands();
	// printf("commmands in g_program.commands: %s\n", g_program.commands[i]);
	do_pipe();
	// last_command();
	// execmd();
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
            execute_commands();
			// i = -1;
		}
		i++;
	}
	printf("do we get to here?\n");
	g_program.commands = g_program.token;
	// last_command();
}