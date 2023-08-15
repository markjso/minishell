/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:05:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/02 14:53:15 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* checks if the input in position token[0]
is one of the builtin shell functions.
Returns 1 if it is and 0 if it is not.
*/
int	is_builtin_cmd(void)
{
	if (!g_program.token || !g_program.token[0])
		return (0);
	if (ft_strcmp(g_program.token[0], "echo") == 0
		|| ft_strcmp(g_program.token[0], "cd") == 0
		|| ft_strcmp(g_program.token[0], "pwd") == 0
		|| ft_strcmp(g_program.token[0], "export") == 0
		|| ft_strcmp(g_program.token[0], "unset") == 0
		|| ft_strcmp(g_program.token[0], "env") == 0
		|| ft_strcmp(g_program.token[0], "exit") == 0)
	{
		return (1);
	}
	return (0);
}

/* if the is_builtin_cmd check passes then it
moves into the do_builtins function to execute
the appropriate builtin*/

void	do_builtins(char **builtin_id)
{
	if (ft_strcmp(builtin_id[0], "echo") == 0)
		echo_cmd(g_program.token);
	if (ft_strcmp(builtin_id[0], "cd") == 0)
		cd_command(g_program.token);
	if (ft_strcmp(builtin_id[0], "pwd") == 0)
		printpwd();
	if (ft_strcmp(builtin_id[0], "export") == 0)
		export_cmd(g_program.token);
	if (ft_strcmp(builtin_id[0], "unset") == 0)
		unset_cmd(g_program.token);
	if (ft_strcmp(builtin_id[0], "env") == 0)
		print_env();
	if (ft_strcmp(builtin_id[0], "exit") == 0)
		ft_exit(0);
}

void	ft_continue(t_token **root)
{
	remove_quotes(root);
	copy_into_array(root);
	if (has_pipe_token() == 1)
	{
		printf("has pipe\n");
		handle_pipe();
	}
	if (is_builtin_cmd())
	{
		do_builtins(g_program.token);
	}
	// else
	// {
	// 	execmd();
	// }
	remove_redirect();
}
