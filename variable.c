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

int	env_len(char *str)
{
	int	i;

	i = 1;
	while (ft_is_valid_var_char(str[i]) == 1)
		i++;
	return (i);
}


char	*return_string(char *src, int terminator)
{
	char *ret;
	static char	*backup;

	if (!src)
		src = backup;

	ret = ft_strdup(src);
	ret[terminator] = '\0';
	return (ret);
}


void	skip_single_quote(char *src, int *end)
{
	(*end)++;
	while (src[*end] != 39 && src[*end] != '\0')
		(*end)++;
	if (src[*end] != '\0')
		(*end)++;
}

void	dollar_found(t_token_list **root, t_token_list *curr, t_token_list *new_node, int *end, int *start)
{
	char	*first;
	char	*env_str;
	int		env_len;
	int		env_start;

	env_start = *end;
	while (ft_is_not_white_space(curr->data[*end] && curr->data[*end] != '\0')
		(*end)++;
	env_str = expand_dollar(ft_substr(curr->data, env_start, *end - env_start));

	*end = env_len(curr->data);
	first = ft_substr(curr->data, *start, env_start;
	new_node = make_new_node(ft_strjoin(temp, env_exp));
	ll_insert_before(root, curr, new_node);
	*start = *end;
}

void	maybe_expand(t_token_list **root, t_token_list *curr, int *join)
{
	int	end;
	int	start;
	t_token_list	*new_node;
	t_token_list	*join_1_node;

	end = 0;
	start = 0;
	*join = 0;
	while(curr->data[end] != '\0')
	{
		if (curr->data[end] == 39) // If is '. Skip over until next ' is found or end of string. 
		{
			skip_single_quote(curr->data, &end);
			continue ;
		}
		if (curr->data[end] == '$')  // If is $
		{
			dollar_found(root, curr, new_node, &end, &start);
			continue ;
		}
		while (curr->data[end] != '\0' && curr->data[end] != '$' && curr->data[end] != 39)
			end++;
		if (curr->data[end] == "$") // If next is $
		{
			*join = 1;
			join_1_node = curr;
			dollar_found(root, curr, new_node, &end, &start);
		}
		new_node = make_new_node((ft_substr(curr->data, start, end - start)));
		ll_insert_before(root, curr, new_node);
		start = end;
		end++;
	}
}




int	find_dollar(char *str)
{
	int i;

	i = 0;
	int	todo = 0;
	while(str[i] != '\0')
	{
		if (str[i] == 39) // If is '. Skip over until next ' is found or end of string. 
		{
			i++;
			while (str[i] != 39 && str[i] != '\0')
				i++;
		}
		if (str[i] == '$') // If is $
			todo++;
		i++;
	}
	return (todo);
}

void    expand_tokens(t_token_list **root)
{
	t_token_list	*curr;
	t_token_list	*temp;
	int				join;

	curr = *root;
	while (curr != NULL)
	{
		maybe_expand(root, curr, &jion);
		temp = curr;
		curr = curr->next;
		ll_remove_node(root, temp);
	}
	ll_print_token(root);

}