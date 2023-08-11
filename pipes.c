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

int    num_of_cmds()
{
    int count;
    int i;

    i = 0;
    count = 1;
    while (&g_program.token[i])
    {
        if (ft_strcmp(&g_program.token[i], "|") == 0 && &g_program.token[i + 1])
        {
            count++;
        }
        i++;
    }
    return (count);
}

void    set_commands()
{
    debugFunctionName("SET_CMDS");
    int i;
    int j;
    int k;
    int num = num_of_cmds();

    g_program.commands = malloc(sizeof(char*) (num + 1)); // MALLOC
    i = 0;
    j = 0;
    k = 0;
    while (&g_program.token[i])
    {
        while (ft_strcmp("|", &g_program.token[i]) != 0 && &g_program.token[i])
        {
            g_program.commands[k][j] = ft_strdup(&g_program.token[i]); // MALLOC
            j++;
            i++;
        }
        g_program.commands[k][j] = NULL;
        if (&g_program.token[i])
            i++;
        k++;
        j = 0;
    }
    if (!&g_program.token[i])
    {
        g_program.commands[k][0] = NULL;
    }
}

void exepipe(void)
{
	debugFunctionName("EXEC_PIPE");
	char **paths;
	char *exec_path;
    char *cmds;
    // int status;

	cmds = g_program.commands[0];
	printf("cmd %s\n", cmds);
	paths = get_full_path();
	exec_path = get_path_for_cmd(paths, cmds);
	if (exec_path)
	{
		printf("Path = %s\n", exec_path);
		for (int i = 0; g_program.commands[i]; i++)
		{
			printf("arg[%i] = %s\n", i, g_program.commands[i]);
		execve(exec_path, &g_program.commands[i], g_program.envp);
		}
		perror("execve"); 
		exit(EXIT_FAILURE); 
	}
	// waitpid(g_program.pid, &status, 0);
	// if (WIFEXITED(status))
	// {
	// 	g_program.exit_status = WEXITSTATUS(status);
	// 	ft_free_array(g_program.commands);
	// }
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

void do_pipe(void)
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
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		wait(&status);
		if (WEXITSTATUS(status) != EXIT_SUCCESS)
			printf("Failed\n");
	}
	else
	{
		close(pipe1[0]);
		dup2(pipe1[1], 1);
		exepipe();
	}
}

void	execute_commands(void)
{
	 debugFunctionName("EXEXUTE_PIPE_COMMAND");
    //  int	i = 0;

	// sig_initialiser();
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
