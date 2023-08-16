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

void	remove_data(t_cmd_token *this_node)
{
	int	i;

	i = 0;
	if (!this_node->data)
		return ;
	while (this_node->data[i])
	{
		free(this_node->data[i]);
		i++;
	}
	free(this_node->data);
}

void	ll_cmd_remove_node(t_cmd_token **root, t_cmd_token *this_node)
{
	t_cmd_token	*curr;

	if (*root == NULL)
		return ;
	if ((*root) == this_node)
	{
		*root = (*root)->next;
		free(this_node->name);
		remove_data(this_node);
		free(this_node);
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
	{
		if (curr->next == this_node)
		{
			curr->next = this_node->next;
			if (this_node->name)
				free(this_node->name);
			remove_data(curr);
			free(this_node);
			return ;
		}
		curr = curr->next;
	}
}

void	ll_cmd_deallocate(t_cmd_token **root)
{
	t_cmd_token	*curr;
	t_cmd_token	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp->name);
		remove_data(curr);
		free(temp->data);
		free(temp);
	}
	*root = NULL;
}

// void	ll_cmd_print_token(t_token **root)
// {
// 	t_token	*curr;

// 	curr = *root;
// 	while (curr != NULL)
// 	{
// 		curr = curr->next;
// 	}
// }
