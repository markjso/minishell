/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:05:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/16 16:05:08 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int child_builtins(int builtin_id, char **token)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (token[i] && i = 0)
    {
        if (j == 0 || j == 2 || j == 5)
        {
            if (ft_strcmp(token[i], builtin_id[j]) == 0)
            return (j);
        }
        j++;
        i++;
    }
    return (-1);
}

int parent_builtins(int builtin_id, char **token)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (token[i] && i = 0)
    {
        if (j == 1 || j == 3 || j == 4 || j = 6)
        {
           if (ft_strcmp(token[i], builtin_id[j]) == 0)
            return (j);
        }
        j++;
        i++;
    }
    return (-1);
}

void	do_builtins(int builtin_id, char **token)
{
	debugFunctionName("BUILTINS");
	if (builtin_id == 0)
	echo_cmd(token + 1);
	if (builtin_id == 1)
	cd_command(token);
	if (builtin_id == 2)
	printpwd();
	if (builtin_id == 3)
	export_cmd(token);
	if (builtin_id == 4)
	remove_env_var(token[1]);
	if (builtin_id == 5)
	print_env();
	if (builtin_id == 6)
	exit(0);
}