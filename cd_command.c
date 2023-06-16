/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:52:18 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/09 11:52:22 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void change_dirs(t_envar *pwd, t_envar *oldpwd, char *cwd)
{
    debugFunctionName("CHANGE_DIR");
    free(oldpwd->value);
    oldpwd->value = ft_strdup(pwd->value);
    printf("%s\n", pwd->value);
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
    // if (tokens[1] == NULL)
    // {
    //     // No directory specified, change to home directory
    //     const char *home = getenv("HOME");
    //     if (home == NULL)
    //     {
    //         printf("cd: HOME environment variable not set\n");
    //         return (1);
    //     }
    //     if (chdir(home) != 0)
    //     {
    //         printf("cd: Failed to change directory\n");
    //         return (1);
    //     }
    // }
    if (chdir(tokens[1]) == 0)
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            printf("cd: Failed to get current directory\n");
            return (1);
        }
        else
            change_dirs(pwd, oldpwd, cwd);
    }
    else
    {
        printf("cd: No such file or directory\n");
        return (1);
    }
    return (0);
}

