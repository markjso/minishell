/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list_create.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:57:39 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/03 15:57:43 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>

#include "minishell.h"

void    ll_insert_end(t_token_list **root, t_token_list *new_node)
{
	t_token_list *curr;
    if (new_node == NULL)
        ft_exit(21);
    if (*root == NULL)
	{
        *root = new_node;
        return;
    }
    curr = *root;
    while(curr->next != NULL)
        curr = curr->next;
    curr->next = new_node;
}

void    ll_insert_beginning(t_token_list **root, t_token_list *new_node)
{
    if (new_node == NULL)
        exit (3);
    new_node->next = *root;

    *root = new_node;
}

void    ll_insert_after(t_token_list *this_node, t_token_list *new_node)
{
		if (new_node == NULL)
		exit (4);
		new_node->next = this_node->next;
		this_node->next = new_node;
}

void	ll_insert_before(t_token_list **root, t_token_list *this_node, t_token_list *new_node)
{
	t_token_list*	curr;

	if (new_node == NULL)
		exit (4);
	if ((*root) == this_node)
	{
		new_node->next = *root;
		*root = new_node;
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
	{
		if (curr->next == this_node)
		{
			new_node->next = curr->next;
			curr->next = new_node;
			return ;
		}
		curr = curr->next;
	}
}
