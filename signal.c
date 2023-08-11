/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:53:36 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/18 14:23:24 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handles the Ctrl-C key combination (SIGINT signal)
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_program.exit_status = 130;
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* if the return value of signal is not SIG_ERR set 
up a new signal with SIGQUIT as first argument and 
SIG_IGN as second argument. SIGQUIT is sent when Ctrl-\
is typed. SIG_IGN tells the system to ignore the
signal so nothing will happen.*/
void	sig_initialiser(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
