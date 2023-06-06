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

static void	init_data(t_data *data)
{
	data->token = (char **)malloc(sizeof(char));
}

int	main(int ac, char **av, char **envp)
{
	int		exec_flag;
	char	input[MAXCOM];
	// char	*parsed_args[MAXLIST];
	t_data	*data = (t_data *)malloc(sizeof(t_data)); // TODO: free(data);
	init_data(data);
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
//			exec_flag = process_input(input, parsed_args);
			// input is data from user, parsed_args/data struct is to be the tokenised string 
			exec_flag = process_input(input, data);
			printf("exec_flag: %d\n", exec_flag);
			if (exec_flag == 1) { // ?? Always 1 ??
				// execmd(parsed_args);
				execmd(data);
			}
		}
	}
	return (EXIT_SUCCESS);
}
