/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:53:36 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/05 15:15:09 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handles the Ctrl-C key combination (SIGINT signal)
void	sig_handler(int sig)
{
	(void)sig;
	write(2, "\n", 1); // Move to a new line
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
}

/* if the return value of signal is not SIG_ERR set 
up a new signal with SIGQUIT as first argument and 
SIG_IGN as second argument. SIGQUIT is sent when Ctrl-\
is typed. SIG_IGN tells the system to ignore the
signal so nothing will happen.*/
void	sig_initialiser(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		printf("failed to catch the signal\n");
	}
	else
		signal(SIGQUIT, SIG_IGN);
}
