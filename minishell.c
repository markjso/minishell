/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:46:42 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/20 17:55:18 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	g_program;

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char input[MAXCOM];
	t_token_list	*root;

    root = NULL;
    g_program.envar = split_env_var(envp);
    g_program.envp = envp;
	init_global();// initilise global variable found in initialise.c
	sig_initialiser();// sets up the signal handling found in signal.c
    while (1)
    {      
        if (take_input(input) == 0)
        {
            g_program.redirect_index = 0;
			//takes input from user and splits it into tokens found in process_input.c
            // Also removes quotes
			process_input(input, &root);
	        check_for_redirect(&root);

        }
    }
    exit(g_program.exit_status);
}
