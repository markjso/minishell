/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <jchurch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:47:33 by jchurch           #+#    #+#             */
/*   Updated: 2023/06/20 11:47:34 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(char *variable)
{
	t_envar *env_node;

	variable++; // Because first is $ sign. 
	env_node = find_env_var(variable);
	return (env_node->value);
}

void    isolate_dollar(t_token_list **root, t_token_list *curr, int start, int length)
{
	char			*before;
	char			*variable;
	char			*expanded;
	char			*join_1;
	char			*join_2;

	before = ft_strdup(curr->data);
	before[start] = '\0';
	curr->data += start; //increment to the $
	variable = ft_strdup(curr->data);
	variable[length] = '\0'; // One after var ends. 
	expanded = ft_strdup(expand_dollar(variable));
	free(variable);
	curr->data += length; //increment to after varible. 
	join_1 = ft_strjoin(before, expanded);
	free(before);
	free(expanded);
	join_2 = ft_strjoin(join_1, curr->data); // Add the rest of the string. 
	free(join_1);
	curr->data = join_2;
	free(join_2);
}

char	**split_var(char *token, int length)
{
	char	*var_name = malloc(sizeof(char) * length + 1);
	char	*after_name = malloc(sizeof(char) * (ft_strlen(token) - length) + 1);

}

int	env_len(char *str)
{
	int	i;

	i = 1;
	while (ft_is_valid_var_char(str[i]) == 1)
		i++;
	return (i);
}

void	find_dollar(t_token_list **root, t_token_list *curr)
{
	int i;
	int length;
	char *temp;

	i = 0;
	length = 0;
	while(curr->data[i] != '\0')
	{
		if (curr->data[i] == 39) // If is '. Skip over until next ' is found or end of string. 
		{
			i++;
			while (curr->data[i] != 39 && curr->data[i] != '\0')
				i++;
		}
		if (curr->data[i] == '$') // If is $
		{
			length = env_len(curr->data);
			if (length > 0) // If valid var char type. 
			{
				isolate_dollar(&root, curr, i, length);
			}
		}
		i++;
	}
}

void    expand_tokens(t_token_list **root)
{
    debugFunctionName("EXPAND_TOKENS");
	t_token_list *curr;

	curr = *root;
	while (curr != NULL)
	{
		find_dollar(&root, curr);
		curr = curr->next;
	}



}