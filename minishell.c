/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:46:42 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/17 12:40:48 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envar	*g_env_vars;

int	main(int ac, char **av, char **envp)
{
	int		execFlag;
	char	input[MAXCOM];
	char	*parsedArgs[MAXLIST];

	execFlag = 0;
	(void)ac;
	(void)av;
	// (void)envp;
	g_env_vars = split_env_var(envp);
	sig_initialiser();
	while (1)
	{
		// IF statement stops else in function from segfaulting. char input becomes *str in function
		if (takeInput(input) == 0)
		{
			execFlag = process_input(input, parsedArgs);
			
			if (execFlag == 1)
				execmd(parsedArgs);
		}
	}
	return (EXIT_SUCCESS);
}
