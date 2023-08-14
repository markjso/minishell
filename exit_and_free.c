/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:55:31 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/02 15:55:42 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_envp(void)
{
	int	i;

	i = 0;
	if (g_program.envp != 0)
	{
		while (g_program.envp[i] != 0)
		{
			free(g_program.envp[i]);
			i++;
		}
		free(g_program.envp);
	}
}

void	ft_free_envar(void)
{
	t_envar	*temp;
	// int		i;

	// i = 0;
	while (g_program.envar != 0)
	{
		temp = g_program.envar;
		g_program.envar = g_program.envar->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

void	ft_token_free(void)
{
	int	i;

	i = 0;
	if (g_program.token)
	{
		while (i < MAXLIST + 1)
		{
			free(g_program.token[i]);
			i++;
		}
		if (g_program.token)
		{
			free (g_program.token);
		}
		if (g_program.token)
			printf("g_program.token still exists\n");
		else
			printf("g_program.token doesnt exists\n");
	}
}

void	ft_free(void)
{
	ft_token_free();
	ft_free_envp();
	ft_free_envar();
}


void	ft_exit(int exit_number)
{
	ft_free();
	check_leaks();
	exit(exit_number);
}

void	ft_exit_cmd_ll(int exit_number, t_cmd_token **root)
{
	if (*root)
	{
		ll_cmd_deallocate(root);
		ft_exit(exit_number);
	}
}
