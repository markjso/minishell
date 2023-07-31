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

// t_program g_program;

void change_dirs(t_envar *pwd, t_envar *oldpwd, char *cwd)
{
    debugFunctionName("CHANGE_DIR");
    free(oldpwd->value);
    oldpwd->value = (char *)ft_strdup(pwd->value);
    free(pwd->value);
    pwd->value = ft_strdup(cwd);
}

int cd_command(char **tokens)
{
    debugFunctionName("CD_CMD");
    char cwd[256];
    t_envar *pwd;
    t_envar *oldpwd;

    pwd = find_env_var("PWD");
    oldpwd = find_env_var("OLDPWD");
    if (chdir(tokens[1]) == 0)
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            (ft_putstr_fd("cd", 2),error_message("Not a directory", 20));
            // return (1);
        }
        else
            change_dirs(pwd, oldpwd, cwd);
    }
    else
    {
        (ft_putstr_fd("cd", 2),error_message("No such file or directory", 2));
        // return (1);
    }
    return (0);
}
