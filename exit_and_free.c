

#include "minishell.h"

t_program	g_program;

void	ft_free_envp()
{
	int	i;

	i = 0;
	if (g_program.envp != 0)
	{
		while (g_program.envp[i] != 0)
		{
			free(g_program.envp[i]);
			i++;
		}
		free(g_program.envp);
	}
}

void	ft_free_envar()
{
	t_envar	*temp;
	int	i;

	i = 0;
	while (g_program.envar != 0)
	{
		temp = g_program.envar;
		g_program.envar = g_program.envar->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

void	ft_token_free()
{
	if (g_program.token)
	{
		for (int i = 0; i < MAXLIST + 1; i++) {
			// printf("token[%d] on exit being freed %s\n", i, g_program.token[i]);
        	free(g_program.token[i]);
		}

		if (g_program.token)
		{
			// printf("g_program.token being freed\n");
			free (g_program.token);
		}
		if (g_program.token)
			printf("g_program.token still exists\n");
		else
			printf("g_program.token doesnt exists\n");
	}
}


void	ft_free()
{
	ft_token_free();
	ft_free_envp();
	ft_free_envar();

}

void	ft_exit(int exit_number)
{
	ft_free();
	check_leaks();
	exit(exit_number);
}