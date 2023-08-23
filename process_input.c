/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:10:49 by jchurch           #+#    #+#             */
/*   Updated: 2023/06/20 18:27:24 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Create a "token" from an input string. 
A token is defined by any word that has a space or tab either side of it. 
Unless it is within matching double or single quotaiton marks. 

Spaces within matching double or single quotation marks are ignored. 
The quotation is treated as one word. 

Any word that has no space or no tab and is next to the "outside" of a 
quotation mark: One token will be created to encompas the outside word 
and the whole quotation mark.*/
char	*make_token(char *str)
{
	int		i;
	char	*return_token;
	int		length;

	i = 0;
	length = find_end(str);
	return_token = malloc(sizeof(char) * length + 1);
	while (i < length)
	{
		return_token[i] = str[i];
		i++;
	}
	return_token[i] = '\0';
	return (return_token);
}

/*Creates a double pointer of type char into **split 
based on the input *str. 

A token is defined by any word that has a space or tab either side of it. 
Unless it is within matching double or single quotaiton marks. 

Spaces within matching double or single quotation marks are ignored. 
The quotation is treated as one word. 

Any word that has no space or no tab and is next to the "outside" of a 
quotation mark: One token will be created to encompas the outside word 
and the whole quotation mark.*/
void	make_tokens(char *str, t_token **root)
{
	int		input_index;
	t_token	*new_node;
	char	*temp_token_value;
	char	pipe_token[2];

	pipe_token[0] = '|';
	pipe_token[1] = '\0';
	input_index = 0;
	while (str[input_index] != '\0')
	{
		if (ft_is_not_white_space(str[input_index]) == 1)
		{
			if (str[input_index] == '|')
				new_node = make_new_node(pipe_token);
			else
			{
				temp_token_value = make_token(&str[input_index]);
				new_node = make_new_node(temp_token_value);
				free(temp_token_value);
				input_index = ft_strlen(new_node->data) - 1 + input_index;
			}
			ll_insert_end(root, new_node);
		}
		input_index++;
	}
}

/*
copy_int_array
Moves linked list t_token->data* into program->token** array. 
*/
void	copy_into_array(t_token **root, t_program *program)
{
	t_token	*curr;
	int		token_number;
	int		i;
	int		j;

	token_number = find_token_number(root);
	i = 0;
	curr = *root;
	while (i < token_number)
	{
		program->token[i] = ft_strdup(curr->data);
		curr = curr->next;
		i++;
	}
	free(program->token[i]);
	program->token[i] = 0;
	ll_deallocate(root);
	j = 0;
	while (j < token_number)
	{
		j++;
	}
}

bool	has_pipe_token(t_program *program)
{
	int	i;

	i = 0;
	while (program->token[i])
	{
		if (program->token[0][0] == '|')
			error_message("command not found", 127);
		else if (program->token[i][0] == '|')
			return (true);
		i++;
	}
	return (false);
}

void	process_input(char *str, t_token **root, t_program *program)
{
	make_tokens(str, root);
	expand_variables(root, program);
}
