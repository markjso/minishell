/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <jchurch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:47:33 by jchurch           #+#    #+#             */
/*   Updated: 2023/06/20 11:47:34 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    expand_tilda(t_program *program, int t)
{
    t_envar *node;

    node = find_env_var("HOME");
    program->token[t] = ft_strdup(node->value);
	printf("%stext", node->value);
}

void     if_special_char(char c, t_program *program, int t)
{
    if (c == '~')
        expand_tilda(program, t);
    return ;
}


void    find_characters(t_program *program)
{
    int     i;
    int     t;
    char    type;

    t = 0;
    type = 39;

    while (program->token[t] != 0)
    {
        i = 0;
        while (program->token[t][i] != '\0')
        {
            if (ft_is_quote(program->token[t][i] == 1)) //IF index i is double or single quote and next exists. 
            {
                if (program->token[t][i] == 34) // Type is double quote, else default to single quote
                    type = 34;
                i++;
                while (program->token[t][i] != type && program->token[t][i] != '\0') // WHILE index i exists and is not (matching/closing) double quote. 
                    i++;
            }
            if_special_char(program->token[t][i], program, t); // Else If a special character ouside of quotes, do somthing
            i++;
        }
        t++;
    }

}

void    variable_expand(t_program *program)
{
    debugFunctionName("VARIABLE_EXPAND");
    find_characters(program);


}