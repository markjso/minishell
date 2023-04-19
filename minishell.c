/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:46:42 by jmarks            #+#    #+#             */
/*   Updated: 2023/04/12 15:47:45 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	int execFlag = 0;
	char input[MAXCOM];
	char *parsedArgs[MAXLIST];
	while (1)
	{
		takeInput(input);
		execFlag = process_input(input, parsedArgs);
		if (execFlag == 1)
		execArgs(parsedArgs);
	}
	// get_path(envp);
	return EXIT_SUCCESS;
}
