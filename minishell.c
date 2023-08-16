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

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	char	input[MAXCOM];
	t_token	*root;
	t_program	program;

	(void)ac;
	(void)av;
	root = NULL;
	init_program(&program, envp);
	sig_initialiser();
	while (1)
	{
		if (take_input(input, &program) == 0)
		{
			program.redirect_index = 0;
			process_input(input, &root, &program);
			check_for_redirect(&root, &program);
		}
	}
}
