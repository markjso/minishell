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

t_program	g_program;

/*
If either STDOUT_FILENO or STDIN_FILENO where modified:
Reset to defualt. 
*/
void	remove_redirect()
{
	if (g_program.out_file > 0)
	{
		close(g_program.out_file);
		dup2(g_program.out_backup, STDOUT_FILENO);
		close(g_program.out_backup);
		free(g_program.redirect_out);
	}
	if (g_program.in_file > 0)
	{
		close(g_program.in_file);
		dup2(g_program.in_backup, STDIN_FILENO);
		close(g_program.in_backup);
		free(g_program.redirect_in);
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

	second = g_program.redirect_index + 1; // One after the quote
	while (str[second] != '\0') // For the length of the string
	{
		if (str[second] == str[g_program.redirect_index]) // If matching quote found
		{
			g_program.redirect_index = second + 1; // Make first be the index of the 2nd quote plus one next outside of the quote. 
			break ; // First will now be one after the matching quote. 
		}
		second++;
	}
	if (str[second] == '\0') // At end and therefore no matching quote was found.
	{
		g_program.redirect_index++; // One after the current quote. 
        return ; // Can remove this return if norm error. 
	}
}

char	*get_file_name(char *str)
{
	int 	end_of_name;
	char	*file_name;

	g_program.redirect_index++;
	while (ft_is_white_space(str[g_program.redirect_index]))
		g_program.redirect_index++;
	end_of_name = g_program.redirect_index;
	while (ft_is_not_white_space(str[end_of_name]) == 1)
		end_of_name++;	
	file_name = ft_substr(str, g_program.redirect_index, end_of_name - g_program.redirect_index);
	if (file_name)
		return (file_name); // MALLOC
	else
		return (NULL);
}

