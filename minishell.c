/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:46:42 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/02 16:38:01 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	input[MAXCOM];
	t_token	*root;

	(void)ac;
	(void)av;
	root = NULL;
	g_program.envar = split_env_var(envp);
	g_program.envp = envp;
	init_global();
	sig_initialiser();
	while (1)
	{
		if (take_input(input) == 0)
		{
			g_program.redirect_index = 0;
			process_input(input, &root);
			check_for_redirect(&root);
		}
	}
}
