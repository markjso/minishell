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

void	ft_free_envp(t_program *program)
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
		free(program->envp);
	}
}

void	ft_free_envar(t_program *program)
{
	t_envar	*temp;

	while (program->envar)
	{
		if (program->envar == NULL)
			break ;
		temp = program->envar;
		program->envar = program->envar->next;
		if (temp->name)
			free(temp->name);
		if (temp->value)
			free(temp->value);
		if (temp)
			free(temp);
	}
}

void	ft_token_free(t_program *program)
{
	int	i;

	i = 0;
	if (program->token)
	{
		while (program->token[i])
		{
			free(program->token[i]);
			i++;
		}
		if (program->token)
		{
			free(program->token);
		}
	}
}

void	ft_free(t_program *program)
{
	ft_token_free(program);
	ft_free_envar(program);
}

void	ft_exit(int exit_number)
{
	check_leaks();
	exit(exit_number);
}
