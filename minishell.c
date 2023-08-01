/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:46:42 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/20 17:55:18 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	g_program;

// static void	free_main_items(char *input)
// {
	// if (g_super.cmds)
	// 	free_cmds(&g_super.cmds);
	// if (g_program.token)
	// 	ft_free_array(g_program.token);
	// if (input)
	// 	free(input);
	// if (prompt)
	// 	free(prompt);
// }

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char input[MAXCOM];
    t_token_list *root;

    root = NULL;
    g_program.envar = split_env_var(envp);
    g_program.envp = envp;
    init_global();
    sig_initialiser();

    while (1)
    {
        if (take_input(input) == 0)
        {
            g_program.redirect_index = 0;
            process_input(input, &root);
            check_for_redirect(&root);
            ft_continue(&root);
        }
    }
}