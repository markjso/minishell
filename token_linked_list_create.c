/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list_create.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:57:39 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/19 14:59:05 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ll_insert_end(t_token **root, t_token *new_node)
{
	t_token	*curr;

	if (new_node == NULL)
		exit(21);
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
