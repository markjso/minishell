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

extern	t_program	g_program;

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char input[MAXCOM];
    int     redirect_index;

    g_program.envar = split_env_var(envp);
    g_program.envp = envp;
	init_global();// initilise global variable found in initialise.c
	sig_initialiser();// sets up the signal handling found in signal.c
    while (1)
    {      
        if (take_input(input) == 0)
        {
            redirect_index = 0;
            check_for_redirect(&g_program, input, &redirect_index);// == 1 || check_for_redirect(&g_program, input, 0) == 2)
            if (g_program.is_redirect > 0)
            {
                do_redirect(&g_program, input, &redirect_index);
            }
			//takes input from user and splits it into tokens found in process_input.c
            // Also removes quotes
			process_input(input, &g_program);
			// if it is one of the builtin commands do it. Found in buitlin_utils.c
            if (is_builtin_cmd(&g_program))
            {
                do_builtins(g_program.token, &g_program);
            }
            else
			// else it is one of the standard shell commands so execute that with execmd. Found in execmd.c
            {
                execmd(&g_program);
            }
        }
    }
    exit(g_program.exit_status);
}
