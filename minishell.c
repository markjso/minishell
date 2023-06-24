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

	g_program.envar = split_env_var(envp);
	init_global();// initilise global variable found in initialise.c
	sig_initialiser();// sets up the signal handling found in signal.c
while (1)
    {      
        if (takeInput(input) == 0)
        {
			//takes input from user and splits it into tokens found in process_input.c
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
    return EXIT_SUCCESS;
}
