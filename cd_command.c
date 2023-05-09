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

int cd_absolute(char **token);
int cd_relative(char **token);

  int cd_command(char **token)
  {
      if (token[1] == NULL)
          return (1);
      if (token[1][0] == '/')
          return (cd_absolute(token));
      else
          return (cd_relative(token));
  }
 
  int cd_absolute(char **token)
  {
      if (chdir(token[1]) != 0)
      {
          printf("%s: No such file or directory\n", token[1]);
          return (1);
      }
      return (0);
  }
 
  int cd_relative2(char *ext, char *cwdext, char **token)
  {
      int i;
 
      i = 0;
      if (chdir(cwdext) != 0)
      {
          printf("%s: No such file or directory\n", token[1]);
          i = 1;
      }
      free(ext);
      free(cwdext);
      return (i);
  }
 
  int cd_relative(char **token)
  {
      char    *cwd;
      char    *ext;
      char    *cwdext;
      int     returnval;
 
      returnval = 0;
      cwd = malloc(PATH_MAX + 1);
      if (getcwd(cwd, PATH_MAX + 1) != NULL)
      {
          ext = ft_strjoin("/", token[1]);
          cwdext = ft_strjoin(cwd, ext);
          returnval = cd_relative2(ext, cwdext, token);
      }
      else
      {
          printf("Error: could not get working directory\n");
          returnval = 1;
      }
      free(cwd);
      return (returnval);
  }