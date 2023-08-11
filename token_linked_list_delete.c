/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list_delete.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:56:59 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/18 15:29:29 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ll_remove_node(t_token **root, t_token *this_node)
{
	t_token	*curr;

	if (*root == NULL)
		return ;
	if ((*root) == this_node)
	{
		*root = (*root)->next;
		free(this_node->data);
		free(this_node);
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
	{
		if (curr->next == this_node)
		{
			curr->next = this_node->next;
			if (this_node->data)
				free(this_node->data);
			free(this_node);
			return ;
		}
		curr = curr->next;
	}
}

void	ll_deallocate(t_token **root)
{
	t_token	*curr;
	t_token	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp->data);
		free(temp);
	}
	*root = NULL;
}

void	ll_print_token(t_token **root)
{
	t_token	*curr;

	curr = *root;
	while (curr != NULL)
	{
		curr = curr->next;
	}
}
