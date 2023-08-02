/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:45:38 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/18 15:32:38 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*make_new_node(char *value)
{
	t_token_list	*new_node;

	new_node = malloc(sizeof(t_token_list));
	if (new_node == NULL)
		ft_exit(20);
	new_node->data = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	replace_node_data(t_token_list *curr, char *new_data)
{
	if (curr == NULL)
		ft_exit(21);
	free(curr->data);
	curr->data = ft_strdup(new_data);
}
