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

// t_program g_program;

void	error_message(char *message, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(message, 2);
	g_program.exit_status = status;
	return ;
}

void	error_message_cmd(char *message, int status)
{
	char	*cmd;

	cmd = g_program.token[1];
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
	g_program.exit_status = status;
	return ;
}

void	error_and_exit(char *message, int status)
{
	char	*cmd;

	cmd = g_program.token[0];
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
	ft_exit(status);
}