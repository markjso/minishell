/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list_delete.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:56:59 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/03 15:57:01 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "minishell.h"

void    ll_remove_node(t_token_list **root, t_token_list *this_node)
{
    t_token_list	*curr; 

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

void    ll_deallocate(t_token_list **root)
{
    t_token_list *curr;
	t_token_list *temp;
	
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

void	ll_print_token(t_token_list **root)
{
	t_token_list *curr = *root;
	while (curr != NULL)
	{
		printf("Current node data: %s\n", curr->data);
		curr = curr->next;
	}
}