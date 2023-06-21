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
	int		exec_flag;
	char	input[MAXCOM];
	char	*parsed_args[MAXLIST];

	exec_flag = 0;
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
			// input is data from user, parsed_args is to be the tokenised string 
			exec_flag = process_input(input, parsed_args);
			printf("Parsed args:\n");
			printf("%s\n", parsed_args[0]);
			printf("%s\n", parsed_args[1]);
			printf("%s\n", parsed_args[2]);
			if (exec_flag == 1) { // ?? Always 1 ??
				execmd(parsed_args);
			}
		}
	}
	return (EXIT_SUCCESS);
}
