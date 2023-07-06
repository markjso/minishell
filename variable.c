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

void    expand_dollar(t_token_list **root, t_token_list *curr, int start, int length)
{
	t_token_list	*new_node;
	char	*temp;
	int i;
	int j;

	i = 0;
	j = 0;
	// Before $ sign
	while (i < start)
	{
		temp[i] = curr->data[i];
		i++;
	}
	temp[i] = '\0';
	make_new_node(temp);
	ll_insert_before(&root, curr, new_node);

	// During $ sign
	while (i < length + start)
	{
		temp[j] = curr->data[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	make_new_node(temp);
	ll_insert_before(&root, curr, new_node);

	j = 0;
	// After variable
	while (curr->data[i] != '\0')
	{
		temp[j] = curr->data[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	make_new_node(temp);
	ll_insert_before(&root, curr, new_node);
	ll_remove_node(&root, curr);
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

	i = 0;
	length = 0;
	while(curr->data[i] != '\0')
	{
		if (curr->data[i] == 39)
		{
			i++;
			while (curr->data[i] != 39 && curr->data[i] != '\0')
				i++;
		}
		if (curr->data[i] == '$')
		{
			length = env_len(curr->data);
			if (length > 0) // if found token, act
			{
				expand_dollar(&root, curr, i, length);
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