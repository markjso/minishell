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

void	change_dirs(t_envar *pwd, t_envar *oldpwd, char *cwd)
{
	free(oldpwd->value);
	oldpwd->value = (char *)ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = ft_strdup(cwd);
}

int	cd_command(char **tokens)
{
	char	cwd[256];
	t_envar	*pwd;
	t_envar	*oldpwd;

	pwd = find_env(g_program.envar, "PWD");
	oldpwd = find_env(g_program.envar, "OLDPWD");
	if (chdir(tokens[1]) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			error_message_cmd("Not a directory", 20);
		}
		else
			change_dirs(pwd, oldpwd, cwd);
	}
	else
	{
		error_message_cmd("No such file or directory", 2);
	}
	return (0);
}
