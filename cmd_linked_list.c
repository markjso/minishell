/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:45:38 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/18 15:32:38 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_num(char **value, int *j)
{
	debugFunctionName("ARG_NUM");
	int		count;
	int		i;

	i = *j;
	count = 0;
	while (value[i] != NULL && ft_strcmp(value[i], "|") != 0)
	{
		i++;
		count++;
	}
	return (count);
}

t_cmd_token	*ll_new_cmd_node(char **value, int *j)
{
	debugFunctionName("LL_NEW_CMD_NODE");
	t_cmd_token	*new_node;
	int			num_args;
	int			i;

	i = 0;
	num_args = arg_num(value, j);
	new_node = malloc(sizeof(t_cmd_token));
	if (new_node == NULL)
		ft_exit(20);
	new_node->name = ft_strdup(value[*j]);
	new_node->data = (char **)malloc(sizeof(char *) * (num_args + 1)); //MALLOC
	if (!new_node->data)
		ft_exit(52);
	while (i < num_args)
	{
		new_node->data[i] = ft_strdup(value[*j]); // MALLOC loop
		i++;
		(*j)++;
	}
	if (value[*j] && ft_strcmp(value[*j], "|") == 0)
		(*j)++;
	new_node->next = NULL;
	return (new_node);
}

void	ll_cmd_insert_end(t_cmd_token **root, t_cmd_token *new_node)
{
	debugFunctionName("LL_CMD_INSERT_END");
	t_cmd_token	*curr;

	if (new_node == NULL)
		exit(21);
	if (*root == NULL)
	{
		*root = new_node;
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
}

void	ll_cmd_insert_beginning(t_cmd_token **root, t_cmd_token *new_node)
{
	if (new_node == NULL)
		exit (3);
	new_node->next = *root;
	*root = new_node;
}

void	ll_cmd_print_token(t_cmd_token **root)
{
	t_cmd_token	*curr;
	int			i;

	printf("Printing cmd linked list\n");
	curr = *root;
	while (curr != NULL)
	{
		i = 0;
		printf("\tPrint cmd LL name: %s\n", curr->name);
		while (curr->data[i])
		{
			printf("\t\tPrint cmd LL [i] data: %d %s\n", i, curr->data[i]);
			i++;
		}
		curr = curr->next;
	}
}