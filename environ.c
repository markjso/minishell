/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:53:33 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/20 18:25:26 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_program g_program;

/*allocates memory for the struct and assigns
name and value to the name and value fields.
Returns a pointer to the new struct.*/
t_envar	*init_env(char *name, char *value)
{
	t_envar	*new;

	new = malloc(sizeof(t_envar));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

/*iterates through the envp array splitting each string
by '=' using ft_split. Then calls init_env to create a 
new struct and append it to the linked list. Start and end
are updated accordingly and a pointer to start is returned*/
t_envar	*split_env_var(char **envp)
{
	char	**split_env;
	t_envar	*start = NULL;
	t_envar	*end = NULL;
	t_envar	*new_node;
	int		i;

	i = 0;
	while (envp[i])
	{
		split_env = ft_split(envp[i], '=');
		if (split_env != NULL && split_env[0] != NULL && split_env[1] != NULL)
		{
			// printf("Split: %s=%s\n", split_env[0], split_env[1]);
			new_node = init_env(ft_strdup(split_env[0]), ft_strdup(split_env[1]));
			if (new_node == NULL)
				printf("Error: memory not allocted\n");
			if (start == NULL)
				start = new_node;
			if (end != NULL)
				end->next = new_node;
			end = new_node;
		}
		i++;
	}
	return (start);
}

/*prints all the environment variables in the linked list
Initialisses tmp to the head of the list and iterates 
through printing the name and value fields. I then updates
tmp to point to the next sturct in the list */

void print_env(void)
{
 debugFunctionName("PRINT_ENV");   
	t_envar *tmp;

	tmp = g_program.envar;
    while (tmp)
    {
        printf("%s=%s\n", tmp->name, tmp->value);
        tmp = tmp->next;
    }
}

/* adds or updates an environment variable to the
list of environment variables. Used by the export
builtin function*/

void add_env_var(t_envar *node)
{
    t_envar *tmp = g_program.envar;

    // Check if an environment variable with the same name already exists
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, node->name) == 0)
        {
            // Update the value of the existing environment variable
            free(tmp->value);
            tmp->value = strdup(node->value);
            rebuild_envp();
			return;
        }
        tmp = tmp->next;
    }
    // If no existing environment variable found, add the new node
    if (g_program.envar == NULL)
    {
        g_program.envar = node;
    }
    else
    {
        tmp = g_program.envar;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
	rebuild_envp();
}

/* search for an environment variable in the 
list of environement variables. Used by the 
export builtin*/

t_envar	*find_env_var(char *name)
{
	t_envar	*tmp;

	tmp = g_program.envar;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}


/* removes an environement variable from the list of
environment variables. Used to unset. Searches through
the list searching for a node with a matching name
if it finds one it removes it from the list and frees
the associated memory*/
void	remove_env_var(char *name)
{
	t_envar	*prev;
	t_envar	*curr;

	prev = NULL;
	curr = g_program.envar;
    // Traverse the list to find the variable
	while (curr != NULL)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
            // Found the variable, remove the node from the list
			if (prev == NULL)
			{
                // Node is the first element in the list
				g_program.envar = curr->next;
			}
			else
			{
                // Node is in the middle or at the end of the list
				prev->next = curr->next;
			}
			free(curr->name);
			free(curr->value);
			free(curr);
			return ;// Exit the function after removing the variable
		}
		prev = curr;
		curr = curr->next;
	}
}