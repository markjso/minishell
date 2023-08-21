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

void	set_commands(t_cmd_token **root, t_program *program)
{
	t_cmd_token	*new_cmd_node;
	int	j;

	j = 0;
	while (program->token[j])
	{
		new_cmd_node = ll_new_cmd_node(program->token, &j);
		ll_cmd_insert_end(root, new_cmd_node);
		// printf("token is now: %s\n", program->token[j]);
	}
	// ll_cmd_print_token(root);
}

void	do_pipe(char *exec_path, t_cmd_token *curr, t_program *program)
{
	int		pipe1[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe1) == -1)
	{
		perror("bad pipe");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe1[0]);
		if (curr->next != NULL)
			dup2(pipe1[1], 1);
		close(pipe1[1]);
		execve(exec_path, curr->data, program->envp);
		perror("execve");
		ft_exit(EXIT_FAILURE);
	}
	close(pipe1[1]);
	dup2(pipe1[0], 0);
	close(pipe1[0]);
	waitpid(pid, &status, 0);
}

void	handle_pipe(t_program *program)
{
	t_cmd_token	*cmd_root;
	t_cmd_token	*curr;
	t_cmd_token	*temp;
	char		*exec_path;
	int			backup[2];

	cmd_root = NULL;
	set_commands(&cmd_root, program);
	curr = cmd_root;
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	while (curr)
	{
		exec_path = get_path_for_cmd(get_full_path(program),
				curr->name, program);
		if (exec_path)
			do_pipe(exec_path, curr, program);
		else
		{
			error_and_continue("exec_path not found", curr->name);
			// temp = curr;
			// curr = curr->next;
			// ll_cmd_remove_node(&cmd_root, temp);
			// continue ;
		}
		temp = curr;
		curr = curr->next;
		ll_cmd_remove_node(&cmd_root, temp);
	}
	cmd_root = NULL;
	dup2(backup[0], 0);
	dup2(backup[1], 1);
	close(backup[0]);
	close(backup[1]);
}
