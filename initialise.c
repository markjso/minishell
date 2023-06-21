/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:44:30 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/20 18:08:12 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_free(char *temp, char *input)
{
	if (input)
		free(input);
	if (temp)
		free(temp);
	
}

int	takeInput(char *str)
{
	char	*input;
	char	*username;
	char	*temp;

	username = getenv("USER");
	temp = ft_strjoin(username, "@>>$ "); // Return is MALLOCED
	input = readline(temp); // Return is MALLOCED
	if (!input) // Input is username and '$'.  IF username doesn't exist or Ctrl-d, exit program in error. 
	{
		printf("%s exit\n", temp);
		free(temp);
		exit(1);
	}
	if (ft_strlen(input) != 0) // If user inputs text, even nonsense, this is called. 
	{
		add_history(input);
		ft_strlcpy(str, input, ft_strlen(input) + 1);
		init_free(temp, input);
		return (0);
	}
	else // Else the user inputed nothing. 
	{
		init_free(temp, input);
		return (1);
	}
}

/* Initialse PWD and OLDPWD to be used in the "cd" butilin
This ensures that they are properly set when the shell
starts up*/

void init_env_vars(void)
{
	char cwd[256];
    t_envar *pwd;
    t_envar *oldpwd;
    
	pwd = init_env(ft_strdup("PWD"), ft_strdup(cwd));
    oldpwd = init_env(ft_strdup("OLDPWD"), ft_strdup(cwd));
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        printf("Failed to get current directory\n");
        exit(1);
    }
    add_env_var(pwd);
    add_env_var(oldpwd);
}

/* sets up the g_program global structure
allocates memory to token to hold an array
of char pointers and sets each element to NULL.
This ensures that array is empty and ready to 
store data.*/

void init_global(void)
{
    g_program.token = (char **)malloc((MAXLIST + 1) * sizeof(char *));
    for (int i = 0; i < MAXLIST + 1; i++) {
        g_program.token[i] = NULL;
	init_env_vars();
    }
}