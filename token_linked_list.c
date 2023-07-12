/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:45:38 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/03 13:45:41 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "minishell.h"

t_token_list    *make_new_node(char *value)
{
    t_token_list *new_node = malloc(sizeof(t_token_list));

    if (new_node == NULL)
        exit(20);
    new_node->data = ft_strdup(value);
    new_node->next = NULL;
    return (new_node);
}

void	replace_node_data(t_token_list *curr, char *new_data)
{
	if (curr == NULL)
		exit(21);
	free(curr->data);
	curr->data = ft_strdup(new_data);
}
