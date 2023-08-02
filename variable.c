/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <jchurch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:47:33 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/18 14:44:32 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	g_program;

char	*ft_first_and_second(char *str, int *start, int env_start, int *end)
{
	char	*first;
	char	*second_temp;
	char	*second;
	char	*first_and_second;

	first = ft_substr(str, *start, env_start);
	second_temp = ft_substr(str, env_start, (*end) - env_start);
	second = ft_strdup(expand_dollar(second_temp));
	free(second_temp);
	first_and_second = ft_strjoin(first, second);
	free(first);
	free(second);
	return (first_and_second);
}

void	dollar_found(t_token_list *curr, int *end, int *start)
{
	char	*first_and_second;
	int		env_start;
	char	*third_temp;
	char	*final;

	env_start = *end;
	while ((curr->data[*end] != '\0') && ft_is_not_white_space(curr->data[*end])
		&& ft_is_not_quote(curr->data[*end]))
		(*end)++;
	first_and_second = ft_first_and_second(curr->data, start, env_start, end);
	*start = *end;
	while (curr->data[*end] != '\0')
		(*end)++;
	third_temp = ft_substr(curr->data, *start, *end - *start);
	final = ft_strjoin(first_and_second, third_temp);
	free(first_and_second);
	free(third_temp);
	replace_node_data(curr, final);
	free(final);
}

void	locate_dollar_for_action(t_token_list *curr)
{
	int	end;
	int	start;

	end = 0;
	start = 0;
	while (curr->data[end] != '\0')
	{
		if (curr->data[end] == 39)
		{
			skip_single_quote(curr->data, &end);
			continue ;
		}
		if (curr->data[end] == '$')
		{
			dollar_found(curr, &end, &start);
			break ;
		}
		while (curr->data[end] != '\0' && curr->data[end] != '$'
			&& curr->data[end] != 39)
			end++;
	}
}

int	count_dollars(char *str)
{
	int	i;
	int	todo;

	i = 0;
	todo = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39 && str[i] != '\0')
				i++;
		}
		if (str[i] == '$')
			todo++;
		i++;
	}
	return (todo);
}

void	expand_variables(t_token_list **root)
{
	t_token_list	*curr;
	int				todo;

	curr = *root;
	while (curr != NULL)
	{
		todo = count_dollars(curr->data);
		while (todo > 0)
		{
			locate_dollar_for_action(curr);
			todo--;
		}
		curr = curr->next;
	}
}
