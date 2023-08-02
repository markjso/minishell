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
void	remove_redirect(void)
{
	if (g_program.redir_out_flag == 1)
	{
		close(g_program.out_file);
		dup2(g_program.out_backup, STDOUT_FILENO);
		close(g_program.out_backup);
		g_program.out_backup = -1;
		free(g_program.redirect_out);
		g_program.redir_out_flag = 0;
	}
	if (g_program.redir_in_flag == 1)
	{
		close(g_program.in_file);
		dup2(g_program.in_backup, STDIN_FILENO);
		close(g_program.in_backup);
		g_program.in_backup = -1;
		free(g_program.redirect_in);
		g_program.redir_in_flag = 0;
	}
}

/*
If a matching close quote is found: 
	Index will be moved to 1 char after the close quote. 

If no matching close quote is found: 
	Index will be moved to 1 char after the current loose quote. 
*/
void	locate_second_quote(char *str)
{
	int		second;

	second = g_program.redirect_index + 1;
	while (str[second] != '\0')
	{
		if (str[second] == str[g_program.redirect_index])
		{
			g_program.redirect_index = second + 1;
			break ;
		}
		second++;
	}
	if (str[second] == '\0')
	{
		g_program.redirect_index++;
		return ;
	}
}

char	*get_file_name(char *str)
{
	int		end_of_name;
	char	*file_name;

	g_program.redirect_index++;
	while (ft_is_white_space(str[g_program.redirect_index]))
		g_program.redirect_index++;
	end_of_name = g_program.redirect_index;
	while (ft_is_not_white_space(str[end_of_name]) == 1)
		end_of_name++;
	file_name = ft_substr(str, g_program.redirect_index, 
			end_of_name - g_program.redirect_index);
	if (file_name)
		return (file_name); 
	else
		return (NULL);
}

void	ft_continue(t_token_list **root)
{
	remove_quotes(root);
	copy_into_array(root);
	// if (has_pipe_token())
	// {
	// 	execute_commands(g_program.token);
	// }
	if (is_builtin_cmd())
	{
		do_builtins(g_program.token);
	}
	else
	{
		execmd();
	}
	remove_redirect();
}

void	check_for_redirect(t_token_list **root)
{
	t_token_list	*curr;
	t_token_list	*prev;
	t_token_list	*temp_token;
	int				flag;

	curr = *root;
	while (curr != NULL)
	{
		flag = 0;
		if (curr == NULL)
			break ;
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
			curr = curr->next->next;
			remove_redirect_tokens(root, temp_token);
			continue ;
		}
		prev = curr;
		curr = curr->next;
	}
	ft_continue(root);
}
