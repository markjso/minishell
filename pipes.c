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

char	**realloc_back(char **arr, char *delim)
{
	debugFunctionName("REALLOC_ARRAY");
    char	**ret;
	int		i;
	int		len;

	if (!delim || !ft_strcmp(arr[0], delim))
		return (arr);
	i = 0;
	while (arr[i] && ft_strcmp(arr[i], delim))
		i++;
	len = i;
	while (arr[len] && ft_strcmp(arr[len], ""))
		len++;
	ret = malloc(sizeof(*ret) * (len - i + 1));
	len = 0;
	while (arr[i] && ft_strcmp(arr[i], ""))
		ret[len++] = ft_strdup(arr[i++]);
	ret[len] = NULL;
	ft_free_array(arr);
	if (!ret[1] && !ft_strcmp(ret[0], ")"))
	{
		ft_free_array(ret);
		return (NULL);
	}
	return (ret);
}
// check to see if input is a pipe
int check_for_pipe(t_program *program)
{
    debugFunctionName("CHECK_FOR_PIPES");
    int i;

    i = 0;
    while(program->token[i])
    {
        if (ft_strcmp(program->token[i], "|") == 0)
            return (1);
        i++; // Found a pipeline command
    }
    return (0); // No pipeline command found
}

void	split_pipes(void)
{
	debugFunctionName("SPLIT_PIPES");
    int     pid;
    int		fd[2];
	
	pipe(fd);
	pid = fork();
	if (pid < 0)
		printf("Error: did not fork\n");
	if (pid)
	{
		if (!g_program.pid)
        g_program.pid = pid;
        close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
        execve(g_program.commands[0], g_program.commands, g_program.envp);
        // perror("Execve error");
        // exit(1);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
        // execve(g_program.commands[0], g_program.commands, g_program.envp);
        waitpid(pid, NULL, 0);
        
	}
}

//populates the commands array with the commands before the "|"
void	set_commands(void)
{
	debugFunctionName("SET_COMMANDS");
    int		i;
	int		j;
	char	**current;

	current = g_program.token;
	i = 0;
	while (current[i] && ft_strcmp("|", current[i]))
		i++;
	if (!current[i])
	{
		g_program.commands = current;
	}
	else
	{
		g_program.commands = malloc(sizeof(*g_program.commands) * (i + 1));
		j = 0;
		while (j < i)
		{
			g_program.commands[j] = current[j];
			j++;
		}
		g_program.commands[i] = NULL;
	}
}

/* separates the commands before with set commands 
splits the pipe to open and close the communication 
and gets the command after the pipe using realloc_back
*/
void	execute_pipe_commands(void)
{
	debugFunctionName("EXECUTE_PIPE_COMMANDS");
    // int	i;

	set_commands();
   	split_pipes();
    execve(g_program.commands[0], g_program.commands, g_program.envp);
	// i = 0;
	// while (g_program.token[i] && ft_strcmp("|", g_program.token[i]))
	// {
	// 	i++;
	// }
	// if (!ft_strcmp("|", g_program.token[i]))
	// {
	// 	g_program.token = realloc_back(g_program.token, "|");
	// 	g_program.token = realloc_back(g_program.token, g_program.token[1]);
	// }
	// i = 0;
	// free(g_program.commands);
}

void	last_command(void)
{
	debugFunctionName("LAST_COMMAND");
    int	pid;

	if (!g_program.pid)
		execmd(&g_program);
	pid = fork();
	if (!pid)
		execmd(&g_program);
	waitpid(g_program.pid, &g_program.exit_status, 0);
	waitpid(pid, &g_program.exit_status, 0);
	free_exit(g_program.exit_status);
}