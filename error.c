/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:19:54 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/03 13:30:56 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program g_program;

void	error_message(char *message, int status)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(message, 2);
	g_program.exit_status = status;
	return ;
}

void	error_and_exit(char *message, int status)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(message, 2);
	exit(status);
}
