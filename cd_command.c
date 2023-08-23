/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:52:18 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/20 17:32:19 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* updates PWD and OLDPWD after a successful
directory change*/

void	change_dirs(t_envar *pwd, t_envar *oldpwd, char *cwd)
{
	free(oldpwd->value);
	oldpwd->value = (char *)ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = ft_strdup(cwd);
}

/* handles the "cd" command. Finds PWD and
OLDPWD in the t_envar list and if chdir is 
successful, checks if getcwd is successful
and if it is uses change_dirs to update them
with the new directory path*/

int	cd_command(char **tokens, t_program *program)
{
	char	cwd[256];
	t_envar	*pwd;
	t_envar	*oldpwd;

	pwd = find_env(program->envar, "PWD");
	oldpwd = find_env(program->envar, "OLDPWD");
	if (tokens[1] == 0)
		return (0);
	if (chdir(tokens[1]) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			error_message_cmd("Not a directory", 20, program);
		}
		else
			change_dirs(pwd, oldpwd, cwd);
	}
	else
	{
		error_message_cmd("No such file or directory", 2, program);
	}
	return (0);
}
