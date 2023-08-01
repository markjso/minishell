

#include "minishell.h"

t_program	g_program;


void	ft_token_free()
{
	if (g_program.token)
	{
		for (int i = 0; i < MAXLIST + 1; i++) {
			printf("token[%d] on exit being freed %s\n", i, g_program.token[i]);
        	free(g_program.token[i]);
		}

		if (g_program.token)
		{
			printf("g_program.token being freed\n");
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
	
}

void	ft_exit(int exit_number)
{
	// ft_free();
	check_leaks();
	exit(exit_number);
}