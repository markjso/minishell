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
t_program g_program;

char	*expand_dollar(char *variable)
{
	debugFunctionName("*EXPAND_DOLLAR");
	t_envar *env_node;

	variable++; // Because first is $ sign. 
	env_node = find_env_var(variable);
	if (env_node == NULL)
	{
		return ("");
	}
	else
	{
		return (env_node->value);
	}
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
	{
		src = backup;
	}
	ret = ft_strdup(src);
	ret[terminator] = '\0';
	return (ret);
}


void	skip_single_quote(char *src, int *end)
{
	debugFunctionName("SKIP_SINGLE_QUOTE");
	(*end)++;
	while (src[*end] != 39)
	{
		(*end)++;
	}
	(*end)++; // End lands on a quote, so increment one more to not be a quote. 
}

void	free_dollar_found(char **env_str, char **first, char **first_2, char **last, char **last_2)
{
	debugFunctionName("FREE_DOLLAR_FOUND");
	if (**env_str)
		free(*env_str);
	if (**first)
		free(*first);
	if (**first_2)
		free(*first_2);
	if (**last)
		free(*last);
	if (**last_2)
		free(*last_2);
}

void	dollar_found(t_token_list *curr, int *end, int *start)
{
	debugFunctionName("DOLLAR_FOUND");

	char	*first;
	char	*first_2;
	char	*env_str;
	int		env_start;
	char	*last;
	char	*last_2;

	env_start = *end;
	while ((curr->data[*end] != '\0') && ft_is_not_white_space(curr->data[*end]) && ft_is_not_quote(curr->data[*end])) 
		(*end)++;
	env_str = ft_strdup(expand_dollar(ft_substr(curr->data, env_start, (*end) - env_start))); // MALLOC
	if (env_str)
		printf("env_str: %s\n", env_str);
	first = ft_substr(curr->data, *start, env_start); // MALLOC
	first_2 = ft_strjoin(first, env_str); // If to many lines merge first_2 and last_2 into lines above each recepcitvly.  // MALLOC
	*start = *end;
	while (curr->data[*end] != '\0')
		(*end)++;
	last = ft_substr(curr->data, *start, *end - *start); // MALLOC
	last_2 = ft_strjoin(first_2, last); // If to many lines merge first_2 and last_2 into lines above each recepcitvly. // MALLOC
	replace_node_data(curr, last_2);
	free_dollar_found(&env_str, &first, &first_2, &last, &last_2); // FREE FREE FREE FREE FREE
}

void	expand_dollar_1(t_token_list *curr)
{
	debugFunctionName("EXPAND_DOLLAR_1");
	int	end;
	int	start;

	end = 0;
	start = 0;
	while(curr->data[end] != '\0')
	{
		if (curr->data[end] == 39) // If is '. Skip over until next ' is found or end of string. 
		{
			skip_single_quote(curr->data, &end);
			continue ;
		}
		if (curr->data[end] == '$')  // If is $
		{
			dollar_found(curr, &end, &start);
			break ;
		}
		while (curr->data[end] != '\0' && curr->data[end] != '$' && curr->data[end] != 39) // Think of this as an else to the 2 ifs. 
			end++;
	}
}

int	count_dollars(char *str)
{
	debugFunctionName("COUNT_DOLLARS");
	int i;
	int	todo;

	i = 0;
	todo = 0;
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
	debugFunctionName("EXPAND_TOKENS");
	t_token_list	*curr;
	int				todo;

	curr = *root;
	while (curr != NULL)
	{
		todo = count_dollars(curr->data);
		while (todo > 0)
		{
			expand_dollar_1(curr);
			todo--;
		}
		curr = curr->next;
	}
	ll_print_token(root);
}