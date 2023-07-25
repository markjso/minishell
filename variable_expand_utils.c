/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expand_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <jchurch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:57:03 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/13 13:57:04 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// t_program g_program;

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


// void	free_dollar_found(char **env_str, char **first, char **first_2, char **last, char **last_2)
// {
// 	debugFunctionName("FREE_DOLLAR_FOUND");
// 	if (**env_str)
// 		free(*env_str);
// 	if (**first)
// 		free(*first);
// 	if (**first_2)
// 		free(*first_2);
// 	if (**last)
// 		free(*last);
// 	if (**last_2)
// 		free(*last_2);
// }