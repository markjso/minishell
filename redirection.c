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

t_program	g_program;

void	remove_redirect_tokens(t_token_list **root, t_token_list *operator_node)
{
	t_token_list	*file_name_node;

	file_name_node = operator_node->next;
	ll_remove_node(root, operator_node);
	ll_remove_node(root, file_name_node);
}

void	std_output(void)
{
	char			*file;
	int				file_temp;

	file = ft_strdup(g_program.redirect_out);
	file_temp = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (file_temp == -1)
		perror("Error in std_input: \n");
	g_program.out_backup = dup(STDOUT_FILENO);
	g_program.out_file = dup2(file_temp, STDOUT_FILENO);
	if (g_program.out_file < 0)
		perror("cannot open output file\n");
	close(file_temp);
	g_program.redir_out_flag = 1;
}

void	std_input(void)
{
	int				file_temp;
	char			*file;

	file = ft_strdup(g_program.redirect_in);
	file_temp = open(file, O_RDONLY, 0444);
	free(file);
	if (file_temp == -1)
		perror("Error in std_input: \n");
	g_program.in_backup = dup(STDIN_FILENO);
	g_program.in_file = dup2(file_temp, STDIN_FILENO);
	if (g_program.in_file < 0)
		perror("Error: cannot open input file\n");
	close(file_temp);
	g_program.redir_in_flag = 1;
}

void	output_append(void)
{
	char			*file;
	int				file_temp;

	file = ft_strdup(g_program.redirect_out);
	file_temp = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(file);
	if (file_temp == -1)
		perror("Error in std_append: \n");
	g_program.out_backup = dup(STDOUT_FILENO);
	g_program.out_file = dup2(file_temp, STDOUT_FILENO);
	if (g_program.out_file < 0)
		perror("Error: cannot open output file\n");
	close(file_temp);
	g_program.redir_out_flag = 1;
}

void	do_redirect(t_token_list *curr, int num, int *flag)
{
	*flag = 1;
	if (curr->next == NULL)
		perror("File not found\n");
	if (num == 1)
	{
		g_program.redirect_out = ft_strdup(curr->next->data);
		std_output();
	}
	else if (num == 2)
	{
		g_program.redirect_out = ft_strdup(curr->next->data);
		output_append();
	}
	else if (num == 3)
	{
		g_program.redirect_in = ft_strdup(curr->next->data);
		std_input();
	}
	else if (num == 4)
	{
		g_program.redirect_in = ft_strdup(curr->next->data);
		input_heredoc(g_program.redirect_in);
	}
}
