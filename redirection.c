/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:00:49 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/17 18:00:09 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_redirect_tokens(t_token **root, t_token *operator_node)
{
	t_token	*file_name_node;

	file_name_node = operator_node->next;
	ll_remove_node(root, operator_node);
	ll_remove_node(root, file_name_node);
}

void	std_output(t_program *program)
{
	char			*file;
	int				file_temp;

	file = ft_strdup(program->redirect_out);
	file_temp = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (file_temp == -1)
		perror("Error in std_input: \n");
	program->out_backup = dup(STDOUT_FILENO);
	program->out_file = dup2(file_temp, STDOUT_FILENO);
	if (program->out_file < 0)
		perror("cannot open output file\n");
	close(file_temp);
	program->redir_out_flag = 1;
}

void	std_input(t_program *program)
{
	int				file_temp;
	char			*file;

	file = ft_strdup(program->redirect_in);
	file_temp = open(file, O_RDONLY, 0444);
	free(file);
	if (file_temp == -1)
	{
		perror("Error in std_input");
		return ;
	}
	program->in_backup = dup(STDIN_FILENO);
	program->in_file = dup2(file_temp, STDIN_FILENO);
	if (program->in_file < 0)
		error_and_exit("no such file", 127, program);
	close(file_temp);
	program->redir_in_flag = 1;
}

void	output_append(t_program *program)
{
	char			*file;
	int				file_temp;

	file = ft_strdup(program->redirect_out);
	file_temp = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(file);
	if (file_temp == -1)
		perror("Error in std_append: \n");
	program->out_backup = dup(STDOUT_FILENO);
	program->out_file = dup2(file_temp, STDOUT_FILENO);
	if (program->out_file < 0)
		perror("Error: cannot open output file\n");
	close(file_temp);
	program->redir_out_flag = 1;
}

void	do_redirect(t_token *curr, int num, int *flag, t_program *program)
{
	*flag = 1;
	if (curr->next == NULL)
		perror("File not found\n");
	if (num == 1)
	{
		program->redirect_out = ft_strdup(curr->next->data);
		std_output(program);
	}
	else if (num == 2)
	{
		program->redirect_out = ft_strdup(curr->next->data);
		output_append(program);
	}
	else if (num == 3)
	{
		program->redirect_in = ft_strdup(curr->next->data);
		std_input(program);
	}
	else if (num == 4)
	{
		program->redirect_in = ft_strdup(curr->next->data);
		input_heredoc(program->redirect_in);
	}
}
