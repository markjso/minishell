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

// t_program g_program;

t_envar	*find_env(t_envar *envars, char *name)
{
	debugFunctionName("FIND_ENV");
	t_envar		*temp;

	temp = envars;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static char	*get_path(char const *currentPath, char const *cmd)
{
	debugFunctionName("GET_PATH");
	char	*rtn;

	if (*cmd == '/')
		rtn = ft_strdup(cmd);
	else if (!ft_strncmp(cmd, "./", 2))
		rtn = ft_strjoin((find_env(g_program.envar, "PWD")->value),
				ft_strjoin("/", cmd));
	else
		rtn = ft_strjoin(currentPath, ft_strjoin("/", cmd));
	return (rtn);
}

char	**get_full_path(void)
{
	debugFunctionName("GET_FULL_PATH");
	char			**env_paths;
	t_envar const	*path;

	path = find_env(g_program.envar, "PATH");
	printf("full path is: %s\n", path->value);
	if (path)
		env_paths = ft_split(path->value, ':');
	else
		env_paths = NULL;
	return (env_paths);
}

char	*get_path_for_cmd(char **env_paths, char const *cmd)
{
	debugFunctionName("GET_CMD_PATH");
	char	*path;
	int		i;

	i = 0;
	while (env_paths[i])
	{
		path = get_path(env_paths[i], cmd);
		if (access(path, F_OK) == 0)
			return (path);
			printf("path for cmd is: %s\n", path);
		free(path);
		i++;
	}
	return (NULL);
}

void	execmd(t_program *program)
{
	debugFunctionName("EXEC_CMD");
	char	**paths;
	char	*exec_path;
    char	*cmds;
    pid_t	pid;
    int		status;

	pid = fork();
	cmds = program->token[0];
    if (pid == 0)
    {
    if (cmds[0] == '/')
	{
		if (execve(&cmds[0], program->token, program->envp) == -1)
			error_and_exit("command cannot be executed", 126);

	}
	paths = get_full_path();
	exec_path = get_path_for_cmd(paths, &cmds[0]);
	printf("exec_path is %s\n", exec_path);
	if (!paths || !exec_path)
		    error_and_exit("command not found", 127);
	if (execve(exec_path, program->token, program->envp) == -1)
		error_and_exit("command cannot be executed", 126);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
			g_program.exit_status = WEXITSTATUS(status);
        }
        // (ft_putstr_fd("minishell", 2), error_message("command not found", 127));
        return;
    }
}

