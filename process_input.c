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

// extern	t_program	g_program;

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
	debugFunctionName("MAKE_TOKEN");
	int		i;
	char	*return_token;

	i = 0;
	int length = find_end(str);
	return_token = malloc(sizeof(char) * length + 1); // malloc freed in return
	while (i < length)
	{
		return_token[i] = str[i];
		i++;
	}
	return_token[i] = '\0';
	// printf("Return_token inbetween q's: q%sq\n", return_token);
	return(return_token);
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
void make_tokens(char *str, t_token_list **root)
{
    debugFunctionName("MAKE_TOKENS");
    int				input_index;
    t_token_list	*new_node;
	char			*temp_token_value;

    input_index = 0;
    while (str[input_index] != '\0')
    {
        if (ft_is_not_white_space(str[input_index]) == 1)
        {
            // Check if the current character is a pipe symbol '|'
            if (str[input_index] == '|')
            {
                char pipe_token[2] = {'|', '\0'};
                new_node = make_new_node(pipe_token);
            }
            else
            {
                // If not a pipe symbol, create a regular token
				temp_token_value = make_token(&str[input_index]); // Malloc
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
Moves linked list t_token_list->data* into program->token** array. 
*/
void	copy_into_array(t_token_list **root)
{
	t_token_list	*curr;
	int		token_number;
	int		i;

	token_number = find_token_number(root);
	i = 0;
	curr = *root;
	while (i < token_number)
	{
		g_program.token[i] = ft_strdup(curr->data);
		// ll_print_token(root);
		curr = curr->next;
		i++;
	}
	g_program.token[i] = 0;
	ll_deallocate(root);

	printf("Printing tokens in Jo's array\n");
	int j = 0;
	while (j < token_number)
	{
		printf("token[%d]: %s\n", j, g_program.token[j]);
		j++;
	}
}

// Implementation of has_pipe_token function
int has_pipe_token(void)
{
    debugFunctionName("HAS_PIPE_TOKEN");
	int i;
	int	count;

	i = 0;
	count = 0;
	while (g_program.token[i])
	{
        if (g_program.token[0][0] == '|')
			error_message("command not found", 127);
		else if (g_program.token[i][0] == '|')
            count++;
        i++;
    }
    return (count);
}

/*
process_input(char *str: raw user input, char **token: is empty pointer to string that will become tokenised string).
Return value is always 0? Why
*/
void process_input(char *str, t_token_list **root)
{
    debugFunctionName("PROCESS_INPUT");

    // Expand variables in the input string
    make_tokens(str, root);
	expand_variables(root);
}

