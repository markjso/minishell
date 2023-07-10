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
			ft_free_array(path_tokens);
			return (location);
		}
		free(location);
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
                error_and_exit("Command not found", 127);
            }
        execve(actual_cmd, program->token, program->envp);
    }
    else
    {
        wait(NULL);
        return;
    }
}

// void	pipex(void)
// {
// 	int		fd[2];
// 	pid_t 	pid;

// 	pipe(fd);
// 	pid = fork();
// 	if (pid < 0)
// 		printf("Error: did not fork\n");
// 	if (pid)
// 	{
// 		close(fd[1]);
// 		dup2(fd[1], 0);
// 		close(fd[0]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], 1);
// 		close(fd[0]);
//         execmd(g_program->token);
// 	}
// }
