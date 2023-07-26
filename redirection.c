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

// t_program g_program;

void	remove_redirect_tokens(t_token_list **root, t_token_list *operator_node)
{
	t_token_list	*file_name_node;

	file_name_node = operator_node->next;
	ll_remove_node(root, operator_node);
	ll_remove_node(root, file_name_node);
}

void std_output()
{
	debugFunctionName("STD_OUT");
	char			*file;
	int				file_temp;

	file = ft_strdup(g_program.redirect_out); // Malloc freed
	file_temp = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (file_temp == -1)
		perror("Error in std_input: \n");
	g_program.out_backup = dup(STDOUT_FILENO);
	g_program.out_file = dup2(file_temp, STDOUT_FILENO);
	if (g_program.out_file < 0)
		perror("Error: cannot open output file\n");
	close(file_temp);
	printf("outfile number: %d\n", g_program.out_file);
}

void	std_input()
{
	debugFunctionName("STD_IN");
	int				file_temp;
	char			*file;

	file = ft_strdup(g_program.redirect_in); // MALLOC freed
	printf("file: %s\n", file);
	file_temp = open(file, O_RDONLY, 0444);
	free(file); //FREE
	if (file_temp == -1)
		perror("Error in std_input: \n");
	printf("tempfile number: %d\n", file_temp);
	g_program.in_backup = dup(STDIN_FILENO);
	printf("backup number: %d\n", g_program.out_backup);
	g_program.in_file = dup2(file_temp, STDIN_FILENO);
	if (g_program.in_file < 0)
		perror("Error: cannot open output file\n");
	close(file_temp);
	printf("infile number: %d\n", g_program.in_file);
}

void	output_append()
{
	debugFunctionName("STD_APPEND");
	char			*file;
	int				file_temp;

	file = ft_strdup(g_program.redirect_out); // Malloc
	file_temp =open(file, O_CREAT | O_WRONLY | O_APPEND , 0644);
	free(file);
	if (file_temp == -1)
		perror("Error in std_append: \n");
	printf("tempfile number: %d\n", file_temp);
	g_program.out_backup = dup(STDOUT_FILENO);
	printf("backup number: %d\n", g_program.out_backup);
	g_program.out_file = dup2(file_temp, STDOUT_FILENO);
	if (g_program.out_file < 0)
		perror("Error: cannot open output file\n");
	close(file_temp);
	printf("outfile number: %d\n", g_program.out_file);
}

void	do_redirect(t_token_list *curr, int num, int *flag)
{
    debugFunctionName("DO_REDIR");

	*flag = 1;
	if (curr->next == NULL)
		perror("File not found\n");
	if (num == 1) // >
	{
		g_program.redirect_out = ft_strdup(curr->next->data); // Malloc freed
		std_output();
	}
	else if (num == 2) // >>
	{
		g_program.redirect_out = ft_strdup(curr->next->data); // Malloc freed
		output_append();
	}
	else if (num == 3)  // <
	{
		g_program.redirect_in = ft_strdup(curr->next->data); //Malloc freed
		std_input();
	}
	else if (num == 4) // <<
	{
		g_program.redirect_in = ft_strdup(curr->next->data);
		input_heredoc(g_program.redirect_in);
	}
}

void	ft_continue(t_token_list **root)
{
	printf("start of ft_continue(root): std out is : %s\n", g_program.redirect_out);
	remove_quotes(root);
	copy_into_array(root);			// if it is one of the builtin commands do it. Found in buitlin_utils.c
	if (is_builtin_cmd())
	{
		do_builtins(g_program.token, &g_program);
	}
	else // else it is one of the standard shell commands so execute that with execmd. Found in execmd.c
	{
		printf("going to else\n");
		execmd(&g_program);
	}
	remove_redirect(); // Reset redirection if changed.
}

void check_for_redirect(t_token_list **root)
{
    debugFunctionName("CHECK_REDIR");
    t_token_list *curr;
    t_token_list *prev;
    t_token_list *temp_token;
    int flag;

    curr = *root;
    while (curr != NULL)
    {
        flag = 0;
        if (curr == NULL)
            break;
        if (curr->data[0] == '<' && curr->data[1] == '<')
        {
            ll_remove_node(root, prev);
            do_redirect(curr, 4, &flag);
        }
        else if (curr->data[0] == '<')
            do_redirect(curr, 3, &flag);
        else if (curr->data[0] == '>' && curr->data[1] == '>')
            do_redirect(curr, 2, &flag);
        else if (curr->data[0] == '>')
            do_redirect(curr, 1, &flag);

        if (flag == 1)
        {
            temp_token = curr;
            curr = curr->next->next; // after the name
            remove_redirect_tokens(root, temp_token); // remove operator and name
            continue;
        }
        prev = curr;
        curr = curr->next;
    }
    ft_continue(root);
}
