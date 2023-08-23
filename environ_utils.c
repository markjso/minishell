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

/*counts the number of elements in the t_envar
linked list and returns the count*/

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

void	rebuild_envp_norm(t_program *program)
{
	int	i;

	i = 0;
	if (program->envp != 0)
	{
		while (program->envp[i] != 0)
		{
			free(program->envp[i]);
			i++;
		}
		if (program->envp)
			free(program->envp);
	}
}

/*Rebuilds the pogram->envp array based on the
t_envar linked list. Used when export or unset
so that the array stays consistent with the 
linked list*/

void	rebuild_envp(t_program *program)
{
	char		*name_part;
	t_envar		*tmp;
	int			count;
	int			i;

	tmp = program->envar;
	count = count_envars(tmp);
	fprintf(stderr, "count %d\n", count);
	i = 0;
	for (int j = 0; program->envp[j]; j++)
		fprintf(stderr, "envp: %d %s\n", j, program->envp[j]);
	program->envp = (char **)malloc(sizeof(char *) * count + 1);
	if (!program->envp)
		return ;
	while (i < count)
	{
		name_part = ft_strjoin(tmp->name, "=");
		program->envp[i] = ft_strjoin(name_part, tmp->value);
		free(name_part);
		i++;
		tmp = tmp->next;
	}
	program->envp[i] = NULL;
	// rebuild_envp_norm(program);
}

/*prints all the environment variables in the linked list
Initialisses tmp to the head of the list and iterates 
through printing the name and value fields. I then updates
tmp to point to the next sturct in the list */

void	print_env(t_program *program)
{
	t_envar	*tmp;

	tmp = program->envar;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	g_exit_status = 0;
	return ;
}
