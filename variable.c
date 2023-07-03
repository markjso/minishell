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

void    expand_dollar(char* token_var, int length)
{
    t_envar *node;

    node = find_env_var("");
    token_var = ft_strdup(node->value);
	printf("%stext", node->value);
}

char	**split_var(char *token, int length)
{
	char	*var_name = malloc(sizeof(char) * length + 1);
	char	*after_name = malloc(sizeof(char) * (ft_strlen(token) - length) + 1);

}

void	expand_token(char *token)
{
	int i;
	int length;

	i = 0;
	length = 0;

	while(token[i] != '\0')
	{
		if (token[i] == '$')
		{
			length = ft_env_word_len(token[i]);
			if (length > 0) // if found token, act
			{
				expand_dollar(token[i], length);
			}
		}
		i++;
	}
}

void    expand_tokens(t_program *program)
{
    debugFunctionName("VARIABLE_EXPAND");
	int j;

	j = 0;
	while (program->token[j] != 0)
	{
	    expand_token(program->token[j]);
		j++;
	}
    find_characters(program);


}