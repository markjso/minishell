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
		fprintf(stderr, "ft_free_envp\n");
	int	i;

	i = 0;
	// for (int j = 0; program->envp[j]; j++)
	// 	fprintf(stderr, "%s\n", program->envp[j]);
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
		fprintf(stderr, "ft_free_envar\n");

	t_envar	*temp;
	int		i;

	i = 0;
	while (program->envar != 0)
	{
		fprintf(stderr, "envar->name: %s\n", program->envar->name);
		fprintf(stderr, "\tenvar->value: %s\n", program->envar->value);
		temp = program->envar;
		program->envar = program->envar->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

void	ft_token_free(t_program *program)
{
	fprintf(stderr, "ft_token_free\n");
	int	i;

	i = 0;
	if (program->token)
	{
		while (i < MAXLIST + 1)
		{
			free(program->token[i]);
			i++;
		}
		if (program->token)
		{
			free (program->token);
		}
		// if (program->token)
		// 	printf("program->token still exists\n");
		// else
		// 	printf("program->token doesnt exists\n");
	}
}

void	ft_free(t_program *program)
{
	fprintf(stderr, "ft_free\n");
	ft_token_free(program);
	ft_free_envp(program);
	ft_free_envar(program);
}

void	ft_exit(int exit_number)
{
	check_leaks();
	exit(exit_number);
}
