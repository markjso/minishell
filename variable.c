/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <jchurch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:47:33 by jchurch           #+#    #+#             */
/*   Updated: 2023/08/22 12:54:02 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_first_and_second(char *str, int var_nbrs[2], int env_start,
			t_program *program)
{
	char	*first;
	char	*second_temp;
	char	*second;
	char	*first_and_second;

	first = ft_substr(str, var_nbrs[0], env_start);
	second_temp = ft_substr(str, env_start, (var_nbrs[1]) - env_start);
	second = ft_strdup(expand_dollar(second_temp, program));
	free(second_temp);
	first_and_second = ft_strjoin(first, second);
	free(first);
	free(second);
	return (first_and_second);
}

void	dollar_found(t_token *curr, int var_nbrs[2], t_program *program)
{
	char	*first_and_second;
	int		env_start;
	char	*third_temp;
	char	*final;

	env_start = var_nbrs[1];
	while ((curr->data[var_nbrs[1]] != '\0')
		&& ft_is_not_white_space(curr->data[var_nbrs[1]])
		&& ft_is_not_quote(curr->data[var_nbrs[1]]))
		(var_nbrs[1])++;
	first_and_second = ft_first_and_second(curr->data, var_nbrs,
			env_start, program);
	var_nbrs[0] = var_nbrs[1];
	while (curr->data[var_nbrs[1]] != '\0')
		(var_nbrs[1])++;
	third_temp = ft_substr(curr->data, var_nbrs[0], var_nbrs[1] - var_nbrs[0]);
	final = ft_strjoin(first_and_second, third_temp);
	free(first_and_second);
	free(third_temp);
	replace_node_data(curr, final);
	free(final);
}

void	locate_dollar_for_action(t_token *curr, t_program *program)
{
	int	var_nbrs[2];

	var_nbrs[0] = 0;
	var_nbrs[1] = 0;
	while (curr->data[var_nbrs[1]] != '\0')
	{
		if (curr->data[var_nbrs[1]] == 39)
		{
			skip_single_quote(curr->data, &var_nbrs[1]);
			continue ;
		}
		if (curr->data[var_nbrs[1]] == '$')
		{
			dollar_found(curr, var_nbrs, program);
			break ;
		}
		while (curr->data[var_nbrs[1]] != '\0' && curr->data[var_nbrs[1]] != '$'
			&& curr->data[var_nbrs[1]] != 39)
			var_nbrs[1]++;
	}
}

char	*local_find_env_name(char *str)
{
	char	*ret_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		i++;
	}
	ret_str = malloc(sizeof(char *) * i);
	while (j < i)
	{
		ret_str[j] = str[j];
		j++;
	}
	ret_str[j] = '\0';
	return (ret_str);
}

void	expand_variables(t_token **root, t_program *program)
{
	t_token	*curr;
	int		todo;
	char	*env_name;

	curr = *root;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->data, "export") == 0 && curr->next != NULL)
		{
			curr = curr->next;
			env_name = local_find_env_name(curr->data);
			if (find_env(program->envar, env_name))
			{
				curr = curr->next;
				continue ;
			}
		}
		todo = count_dollars(curr->data);
		while (todo > 0)
		{
			locate_dollar_for_action(curr, program);
			todo--;
		}
		curr = curr->next;
	}
}
