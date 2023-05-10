/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:53:33 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/09 15:53:36 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_env(char **envp)
{
  int count;

  count = 0;
  while (envp[count])
    count++;
  return (count);
}

t_envar *split_env_var(char **envp)
{
  char  **split_env;
  t_envar   *tmp;
  int nbr_of_envs;
  int i;
    
  i = 0;
  nbr_of_envs = count_env(envp);
  tmp = malloc(sizeof(t_envar) * (nbr_of_envs + 1));
  if (tmp == NULL) {
    return NULL;
  }
  
  while (envp[i])
  {
    split_env = ft_split(envp[i], '=');
    if (split_env != NULL && split_env[0] != NULL && split_env[1] != NULL)
    {
      tmp[i].name = ft_strdup(split_env[0]);
      tmp[i].value = ft_strdup(split_env[1]);
      i++;
    }
  }
  // terminate the array with a NULL name
  tmp[i].name = NULL;
  tmp[i].value = NULL;

  return (tmp);
}

void  print_env(t_envar *envp)
{
  int i;

  i = 0;
  while(envp[i].name)
  {
      printf("%s=%s\n", envp[i].name, envp[i].value);
      i++;
  }
}
