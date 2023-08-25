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

static char	*get_user_prompt(void)
{
	char	*prompt;
	char	*username;
	char	*temp;

	prompt = ft_strdup(T_DEFAULT);
	username = getenv("USER");
	if (username)
	{
		temp = ft_strjoin(prompt, username);
		free(prompt);
		prompt = ft_strjoin(temp, "J++minishell@>>$ ");
		free(temp);
	}
	else
		printf("username does not exist\n");
	return (prompt);
}

/* Stores the user prompt and uses readline to enable
line editing and command history. If user_input is
null it means ctrl-D was entered and it prints exit
and exits the shell. If is not null then it copies
the user input to input, adds to the history using 
add_history, frees the memory and returns '0'*/

int	take_input(char *input, t_program *program)
{
	char	*user_input;
	char	*prompt;

	prompt = get_user_prompt();
	user_input = readline(prompt);
	free(prompt);
	if (!user_input)
	{
		printf("exit\n");
		ft_free(program);
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

void	init_env_vars(t_program *program)
{
	char	cwd[256];
	t_envar	*pwd;
	t_envar	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("Failed to get current directory\n");
		ft_free(program);
		ft_exit(1);
	}
	pwd = init_env("PWD", cwd);
	oldpwd = init_env("OLDPWD", cwd);
	add_env_var(pwd, program);
	add_env_var(oldpwd, program);
	free(pwd->name);
	free(pwd->value);
	free(pwd);
	free(oldpwd->name);
	free(oldpwd->value);
	free(oldpwd);
}

/* sets up the t_program structure
allocates memory to token to hold an array
of char pointers and sets each element to NULL.
This ensures that array is empty and ready to 
store data.*/

void	init_program(t_program *program, char **envp)
{
	int	i;

	i = 0;
	program->token = (char **)malloc((MAXLIST + 1) * sizeof(char *));
	while (i < MAXLIST + 1)
	{
		program->token[i] = NULL;
		i++;
	}
	program->envar = split_env_var(envp);
	init_envp_first_run(program, envp);
	program->token[i] = NULL;
	init_env_vars(program);
}

/*allocates memory for the t_envar struct and assigns
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
