/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <jchurch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:52:37 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/13 14:52:38 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_program g_program;

void    really_remove_quotes(t_token_list *curr, int *start, int first, int second)
{
    char    *str_first; 
    char    *str_second;
    char    *first_and_second;
    char    *str_third;
    char    *new_node_data;

    str_first = ft_substr(curr->data, start, first - *start); // MALLOC freed
    first++; // Next beyond the first quote
    str_second = ft_substr(curr->data, first, second - first); // MALLOC freed
    first_and_second = ft_strjoin(str_first, str_second); // MALLOC freed
    free(str_first);
    free(str_second);
    second++; // Next beyond the matching quote. 
    first = second;
    *start = second;
    while (curr->data[second] != '\0')
        second++;
    str_third = ft_substr(curr->data, first, second - first); // MALLOC freed
    new_node_data = ft_strjoin(first_and_second, str_third); // MALLOC freed
    free(first_and_second); 
    free(str_third);
    replace_node_data(curr, new_node_data);
    free(new_node_data);
    *start -= 2; //Because we just removed 2 items from the string. 
}


void    find_second_quote(t_token_list *curr, int *start, int first)
{
    int second;
    second = first + 1;
    while (curr->data[second] != '\0')
    {
        if (curr->data[second] == curr->data[first]) //Match found
        {
            really_remove_quotes(curr, &start, first, second);
            break ;
        }
        second++;
    }
}

void    remove_quotes(t_token_list **root)
{
    int             start;
    int             first;
    t_token_list    *curr;

    curr = *root;

    while (curr != NULL)
    {
        start = 0;
        while (curr->data[first] != '\0')
        {
            if (ft_is_quote(curr->data[first]) == 1)
            {
                find_second_quote(curr, &start, first);
                continue ;
            }
            first++;
        }
        curr = curr->next;
    }
}
