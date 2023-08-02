/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:04:38 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/02 15:38:38 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envars(t_envar *envars)
{
	int		i;
	t_envar	*tmp;

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
	char		*name_part;
	t_envar		*tmp;
	int			count;
	int			i;

	ft_free_envp();
	tmp = g_program.envar;
	count = count_envars(tmp);
	i = 0;
	new_env = malloc(sizeof(char *) * count + 1);
	if (!new_env)
		return ;
	while (i < count)
	{
		name_part = ft_strjoin(tmp->name, "=");
		new_env[i] = ft_strjoin(name_part, tmp->value);
		free(name_part);
		i++;
		tmp = tmp->next;
	}
	new_env[i] = NULL;
	g_program.envp = new_env;
}

/*prints all the environment variables in the linked list
Initialisses tmp to the head of the list and iterates 
through printing the name and value fields. I then updates
tmp to point to the next sturct in the list */

void	print_env(void)
{
	t_envar	*tmp;

	tmp = g_program.envar;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	g_program.exit_status = 0;
	return ;
}
