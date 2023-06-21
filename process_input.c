/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:10:49 by jchurch           #+#    #+#             */
/*   Updated: 2023/06/20 18:27:24 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_program	g_program;

void parse_input(char *str, t_program *program)
{
    debugFunctionName("PARSE_INPUT");
    char **split = ft_split(str, ' '); // Split the input string

    // Count the number of tokens in the split array
    int num_tokens = 0;
    while (split[num_tokens]) {
        num_tokens++;
    }

    // Allocate memory for program->token
    program->token = (char **)malloc((num_tokens + 1) * sizeof(char *));

    int i = 0;
    while (split[i]) {
        program->token[i] = ft_strdup(split[i]); // Copy each token to program->token
        i++;
    }
    program->token[i] = NULL; // Add a NULL terminator to mark the end of tokens

    free(split); // Free the split tokens
}