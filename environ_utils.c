/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:04:38 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/27 16:04:40 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_program g_program;

int     count_envars(t_envar *envars)
{
    int     i;
    t_envar *tmp;

    tmp = envars;
    i = 0;

    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

void	rebuild_envp(void)
{
	char		**new_env;
	t_envar		*tmp;
	int			count;
	int			i;

	if (g_program.envp != NULL)
		free(g_program.envp);
	tmp = g_program.envar;
	count = count_envars(tmp);
	i = 0;
	new_env = malloc(sizeof(char *) * count + 1);
	if (!new_env)
		return ;
	while (i < count)
	{
		new_env[i] = ft_strdup(tmp->name);
		new_env[i] = ft_strjoin(new_env[i], "=");
		new_env[i] = ft_strjoin(new_env[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	new_env[i] = NULL;
	g_program.envp = new_env;
}
