/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:53:33 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/02 15:47:47 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_new_split(char **split_env)
{
	int	i;

	i = 0;
	while (split_env[i])
	{
		free(split_env[i]);
		i++;
	}
	free(split_env);
}

/*iterates through the envp array splitting each string
by '=' using ft_split. Then calls init_env to create a 
new struct and append it to the linked list. Start and end
are updated accordingly and a pointer to start is returned*/
t_envar	*split_env_var(char **envp)
{
	char	**split_env;
	t_envar	*start;
	t_envar	*end;
	t_envar	*new_node;
	int		i;

	i = 0;
	start = NULL;
	end = NULL;
	while (envp[i])
	{
		split_env = ft_split(envp[i], '=');
		new_node = init_env(split_env[0], split_env[1]);
		if (new_node == NULL)
			printf("Error: memory not allocted\n");
		if (start == NULL)
			start = new_node;
		if (end != NULL)
			end->next = new_node;
		end = new_node;
		i++;
		free_new_split(split_env);
	}
	return (start);
}

/* adds or updates an environment variable to the
list of environment variables. Used by the export
builtin function*/

void	add_env_var(t_envar *node, t_program *program)
{
	t_envar	*tmp;

	tmp = program->envar;
	while (tmp != NULL)
	{
		if (strcmp(tmp->name, node->name) == 0)
		{
			fprintf(stderr, "add_env_var_upper %s\n", node->name);
			free(tmp->value);
			tmp->value = strdup(node->value);
			rebuild_envp(program);
			return ;
		}
		tmp = tmp->next;
	}
	if (program->envar == NULL)
		program->envar = node;
	else
	{
		tmp = program->envar;
		while (tmp->next != NULL)
		{
			fprintf(stderr, "while add_env_var lower %s\n", tmp->name);
			tmp = tmp->next;
		}
		tmp->next = node;
	}
	tmp = program->envar;
	while (tmp != NULL)
	{
		fprintf(stderr, "while add_env_var bottom %s\n", tmp->name);
		tmp = tmp->next;
	}
	rebuild_envp(program);
}

/* search for an environment variable in the 
list of environement variables. Used by the 
export builtin*/

t_envar	*find_env(t_envar *envars, char *name)
{
	t_envar		*temp;

	temp = envars;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp);
		temp = temp->next;
	}
	fprintf(stderr, "return null\n");
	return (NULL);
}

/* removes an environement variable from the list of
environment variables. Used to unset. Searches through
the list searching for a node with a matching name
if it finds one it removes it from the list and frees
the associated memory*/
void	remove_env_var(char *name, t_program *program)
{
	t_envar	*prev;
	t_envar	*curr;

	prev = NULL;
	curr = program->envar;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			if (prev == NULL)
			{
				program->envar = curr->next;
			}
			else
			{
				prev->next = curr->next;
			}
			free(curr->name);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
