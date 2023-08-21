/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:01:04 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/17 18:01:07 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
If either STDOUT_FILENO or STDIN_FILENO were modified:
Reset to defualt. 
*/
void	remove_redirect(t_program *program)
{
	if (program->redir_out_flag == 1)
	{
		close(program->out_file);
		dup2(program->out_backup, STDOUT_FILENO);
		close(program->out_backup);
		program->out_backup = -1;
		free(program->redirect_out);
		program->redir_out_flag = 0;
	}
	if (program->redir_in_flag == 1)
	{
		close(program->in_file);
		dup2(program->in_backup, STDIN_FILENO);
		close(program->in_backup);
		program->in_backup = -1;
		free(program->redirect_in);
		program->redir_in_flag = 0;
	}
}

int	redirect_arrows(t_token *norm[2], int *f, t_token **root, t_program *prog)
{
	if (norm[1]->data[0] == '<' && norm[1]->data[1] == '<')
	{
		ll_remove_node(root, norm[0]);
		do_redirect(norm[1], 4, f, prog);
	}
	else if (norm[1]->data[0] == '<')
		do_redirect(norm[1], 3, f, prog);
	else if (norm[1]->data[0] == '>' && norm[1]->data[1] == '>')
		do_redirect(norm[1], 2, f, prog);
	else if (norm[1]->data[0] == '>')
		do_redirect(norm[1], 1, f, prog);
	if (*f == 2)
	{
		ll_deallocate(root);
		return (-1);
	}
	return (1);
}

void	check_for_redirect(t_token **root, t_program *program)
{
	t_token	*norm[2];
	t_token	*temp_token;
	int		flag;

	norm[1] = *root;
	while (norm[1] != NULL)
	{
		flag = 0;
		if (norm[1] == NULL)
			break ;
		if (redirect_arrows(norm, &flag, root, program) == -1)
			return ;
		if (flag == 1)
		{
			temp_token = norm[1];
			norm[1] = norm[1]->next->next;
			remove_redirect_tokens(root, temp_token);
			continue ;
		}
		norm[0] = norm[1];
		norm[1] = norm[1]->next;
	}
	ft_continue(root, program);
}
