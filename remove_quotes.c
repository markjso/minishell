/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <jchurch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:52:37 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/19 14:59:55 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	g_program;

char	*make_one_and_two(t_token_list *curr, int *start, 
		int *first, int *second)
{
	char	*str_first;
	char	*str_second;
	char	*first_and_second;

	str_first = ft_substr(curr->data, *start, *first - *start);
	(*first)++;
	str_second = ft_substr(curr->data, *first, *second - *first);
	first_and_second = ft_strjoin(str_first, str_second);
	free(str_first);
	free(str_second);
	second++;
	return (first_and_second);
}

void	really_remove_quotes(t_token_list *curr, int *start, 
		int *first, int second)
{
	char	*first_and_second;
	char	*str_third;
	char	*new_node_data;
	int		end;

	first_and_second = make_one_and_two(curr, start, first, &second);
	second++;
	end = second;
	while (curr->data[end] != '\0')
		end++;
	str_third = ft_substr(curr->data, second, end - second);
	new_node_data = ft_strjoin(first_and_second, str_third);
	free(first_and_second);
	free(str_third);
	replace_node_data(curr, new_node_data);
	free(new_node_data);
	*first = second - 2;
}

void	find_second_quote(t_token_list *curr, int *start, int *first)
{
	int	second;

	second = *first + 1;
	while (curr->data[second] != '\0')
	{
		if (curr->data[second] == curr->data[*first])
		{
			really_remove_quotes(curr, start, first, second);
			return ;
		}
		second++;
	}
	if (curr->data[second] == '\0')
	{
		(*first)++;
		return ;
	}
}

void	remove_quotes(t_token_list **root)
{
	int				start;
	int				first;
	t_token_list	*curr;

	curr = *root;
	while (curr != NULL)
	{
		start = 0;
		first = 0;
		while (curr->data[first] != '\0')
		{
			if (ft_is_quote(curr->data[first]) == 1)
			{
				find_second_quote(curr, &start, &first);
				continue ;
			}
			first++;
		}
		curr = curr->next;
	}
}
