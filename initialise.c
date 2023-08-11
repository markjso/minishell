/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:44:30 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/02 16:30:26 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_user_prompt(void)
{
	char	*prompt;
	t_envar	*username;

	prompt = ft_strdup(T_DEFAULT);
	username = find_env(g_program.envar, "USER");
	if (username)
	{
		prompt = ft_strjoin(prompt, (char *)username->value);
		prompt = ft_strjoin(prompt, "@>>$ ");
	}
	g_program.prompt = ft_strdup(prompt);
}

int	take_input(char *input)
{
	char	*user_input;

	get_user_prompt();
	user_input = readline(g_program.prompt);
	if (!user_input)
	{
		printf("exit\n");
		ft_exit(1);
	}
	if (ft_strlen(user_input) != 0) 
	{
		ft_strlcpy(input, user_input, MAXCOM - 1);
		add_history(user_input);
		free(user_input);
		return (0);
	}
	else
	{
		free(user_input);
		return (1);
	}
}

/* Initialse PWD and OLDPWD to be used in the "cd" butilin
This ensures that they are properly set when the shell
starts up*/

void	init_env_vars(void)
{
	char	cwd[256];
	t_envar	*pwd;
	t_envar	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("Failed to get current directory\n");
		ft_exit(1);
	}
	pwd = init_env("PWD", cwd);
	oldpwd = init_env("OLDPWD", cwd);
	add_env_var(pwd);
	add_env_var(oldpwd);
	free(pwd->name);
	free(pwd->value);
	free(pwd);
	free(oldpwd->name);
	free(oldpwd->value);
	free(oldpwd);
}

/* sets up the g_program global structure
allocates memory to token to hold an array
of char pointers and sets each element to NULL.
This ensures that array is empty and ready to 
store data.*/

void	init_global(void)
{
	int	i;

	i = 0;
	g_program.token = (char **)malloc((MAXLIST + 1) * sizeof(char *));
	while (i < MAXLIST + 1)
	{
		i++;
	}
	g_program.token[i] = NULL;
	g_program.envp = NULL;
	g_program.exit_status = 0;
	init_env_vars();
}

/*allocates memory for the struct and assigns
name and value to the name and value fields.
Returns a pointer to the new struct.*/
t_envar	*init_env(char *name, char *value)
{
	t_envar	*new;

	new = malloc(sizeof(t_envar));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name); 
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}
