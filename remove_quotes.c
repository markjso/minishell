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


// a"b"c"d"e \0
// 012345678  9

// abc"d"e \0
// 0123456  7

// abcde \0
// 01234  5

// start = 6;
// first = 4;
// second 7;

char    *make_one_and_two(t_token_list *curr, int *start, int *first, int *second)
{
    char    *str_first;
    char    *str_second;
    char    *first_and_second;

    str_first = ft_substr(curr->data, *start, *first - *start); // MALLOC freed
    (*first)++; // One beyone the quote
    str_second = ft_substr(curr->data, *first, *second - *first); // MALLOC freed
    first_and_second = ft_strjoin(str_first, str_second); // MALLOC and I know it (taken care of in return)
    free(str_first);
    free(str_second);
    second++;
    return (first_and_second);
}

void    really_remove_quotes(t_token_list *curr, int *start, int *first, int second)
{
    char    *first_and_second;
    char    *str_third;
    char    *new_node_data;
    int     end;

    first_and_second = make_one_and_two(curr, start, first, &second); // MALLOC 
    second++; // Next beyond the matching quote. (This may become first if there are more quote pairs.)
    end = second;
    while (curr->data[end] != '\0')
        end++;
    str_third = ft_substr(curr->data, second, end - second); // MALLOC freed
    new_node_data = ft_strjoin(first_and_second, str_third); // MALLOC freed
    free(first_and_second); 
    free(str_third);
    replace_node_data(curr, new_node_data); // MALLOC (oh yea)
    free(new_node_data);
    *first = second - 2; // Second - 2 (we just removed 2 cells from the array and want the next char that would have been after the 2nd quote.)
}

void    find_second_quote(t_token_list *curr, int *start, int *first)
{
    int second;
    second = *first + 1;
    while (curr->data[second] != '\0')
    {
        if (curr->data[second] == curr->data[*first]) //Match found
        {
            really_remove_quotes(curr, start, first, second);
            return ; // Can be 'break;' if norm error
        }
        second++;
    }
    if (curr->data[second] == '\0') // At end and therefore no matching quote was found. 
    {
        (*first)++;
        return ; // Can remove this return if norm error. 
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
        first = 0;
        while (curr->data[first] != '\0')
        {
            // start = first;
            if (ft_is_quote(curr->data[first]) == 1)
            {
                find_second_quote(curr, &start, &first);
                continue ;
            }
            first++;
        }
        curr = curr->next;
    }
}
