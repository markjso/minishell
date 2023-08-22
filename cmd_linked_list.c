/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:45:38 by jchurch           #+#    #+#             */
/*   Updated: 2023/08/22 13:06:27 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_num(char **value, int *j)
{
	int		count;
	int		i;

	i = *j;
	count = 0;
	while (value[i] != NULL && ft_strcmp(value[i], "|") != 0)
	{
		i++;
		count++;
	}
	return (count);
}

t_cmd_token	*ll_new_cmd_node(char **value, int *j)
{
	t_cmd_token	*new_node;
	int			num_args;
	int			i;

	i = 0;
	num_args = arg_num(value, j);
	new_node = malloc(sizeof(t_cmd_token));
	if (new_node == NULL)
		ft_exit(20);
	new_node->name = ft_strdup(value[*j]);
	new_node->data = (char **)malloc(sizeof(char *) * (num_args + 1));
	if (!new_node->data)
		ft_exit(52);
	while (i < num_args)
	{
		new_node->data[i] = ft_strdup(value[*j]);
		i++;
		(*j)++;
	}
	new_node->data[i] = NULL;
	if (value[*j] && ft_strcmp(value[*j], "|") == 0)
		(*j)++;
	new_node->next = NULL;
	return (new_node);
}

void	ll_cmd_insert_end(t_cmd_token **root, t_cmd_token *new_node)
{
	t_cmd_token	*curr;

	if (new_node == NULL)
		ft_exit(21);
	if (*root == NULL)
	{
		*root = new_node;
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
}
