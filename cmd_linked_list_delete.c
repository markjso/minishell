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
		while (temp->data)
		{
			free(*temp->data);
			temp->data++;
		}
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
