/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:30:25 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/20 18:26:35 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program g_program;

char	*get_location(char *cmd)
{
	debugFunctionName("GET_LOCATION");
    char	**path_tokens;
	char	*path;
	char	*location;
	int		i;

	path = getenv("PATH");
   	//split into directories
	path_tokens = ft_split(path, ':');
	i = 0;
	while (path_tokens[i])
	{
		//append "/" to the directory
		location = ft_strjoin(path_tokens[i], "/");
        //append the command name 
		location = ft_strjoin(location, cmd);
        //check if the command exists and if it does return it
		if (access(location, F_OK) == 0)
		{
			// ft_free_array(path_tokens);
			return (location);
		}
		// free(location);
		i++;
    }
	ft_free_array(path_tokens);
    free(location);
	return (NULL);
}

void execmd(t_program *program)
{
    debugFunctionName("EXECMD");
    pid_t pid;
    char *cmd;
    char    *actual_cmd;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("Error: fork failed\n");
    }
    else if (pid == 0)
    {
        cmd = program->token[0];
        actual_cmd = get_location(cmd);
        if (actual_cmd == NULL)
            {
                error_and_exit(127);
            }
        execve(actual_cmd, program->token, program->envp);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            g_program.exit_status = WEXITSTATUS(status);
        }
        return;
    }
}
