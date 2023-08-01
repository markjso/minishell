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
		free(path);
		i++;
	}
	return (NULL);
}

<<<<<<< HEAD
void	execmd(void)
=======

void exe_pipe_cmd(char **command_tokens) {
    debugFunctionName("EXEC_PIPE_CMD");
    char **paths;
    char *exec_path;
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (command_tokens[0][0] == '/') {
            if (execve(command_tokens[0], command_tokens, g_program.envp) == -1) {
                perror("Error");
                ft_exit(EXIT_FAILURE);
            }
        }

        paths = get_full_path();
        exec_path = get_path_for_cmd(paths, command_tokens[0]);
        if (!paths || !exec_path) {
            perror("Command not found");
            ft_exit(EXIT_FAILURE);
        }
        if (execve(exec_path, command_tokens, g_program.envp) == -1) {
            perror("Error");
            ft_exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            g_program.exit_status = WEXITSTATUS(status);
        }
    }
}

void	execmd(t_program *program)
>>>>>>> 1c9efd5a79e5b9fd15775f0d175c768737493f7c
{
	debugFunctionName("EXEC_CMD");
	char	**paths;
	char	*exec_path;
    char	*cmds;
    pid_t	pid;
    int		status;

	pid = fork();
	cmds = g_program.token[0];
    if (pid == 0)
    {
    if (cmds[0] == '/')
	{
		if (execve(&cmds[0], g_program.token, g_program.envp) == -1)
			error_and_exit("command cannot be executed", 126);
	}
	paths = get_full_path();
	exec_path = get_path_for_cmd(paths, &cmds[0]);
	if (!paths || !exec_path)
		    error_and_exit("command not found", 127);
	if (execve(exec_path, g_program.token, g_program.envp) == -1)
		error_and_exit("command cannot be executed", 126);
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
	exit(EXIT_SUCCESS);
}
