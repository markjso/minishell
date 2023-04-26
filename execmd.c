/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exexmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:30:25 by jmarks            #+#    #+#             */
/*   Updated: 2023/04/17 15:30:28 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_location(char *command)
{
    char *path, *path_copy, *path_token, *file_path;
    int command_length, directory_length;
    struct stat buffer;

    path = getenv("PATH");

    if (path)
    {
        /* Duplicate the path string -> remember to free up memory for this because strdup allocates memory that needs to be freed*/ 
        path_copy = ft_strdup(path);
        /* Get length of the command that was passed */
        command_length = ft_strlen(command);

        /* Let's break down the path variable and get all the directories available*/
        path_token = strtok(path_copy, ":");

        while(path_token != NULL)
        {
            /* Get the length of the directory*/
            directory_length = strlen(path_token);
            /* allocate memory for storing the command name together with the directory name */
            file_path = malloc(command_length + directory_length + 2); /* NB: we added 2 for the slash and null character we will introduce in the full command */
            /* to build the path for the command, let's copy the directory path and concatenate the command to it */
            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, command);
            strcat(file_path, "\0");

            /* let's test if this file path actually exists and return it if it does, otherwise try the next directory */
            if (stat(file_path, &buffer) == 0){
                /* return value of 0 means success implying that the file_path is valid*/

                /* free up allocated memory before returning your file_path */
                free(path_copy);

                return (file_path);
            }
            else{
                /* free up the file_path memory so we can check for another path*/
                free(file_path);
                path_token = strtok(NULL, ":");

            }

        }
        /* if we don't get any file_path that exists for the command, we return NULL but we need to free up memory for path_copy */ 
        free(path_copy);
        /* before we exit without luck, let's see if the command itself is a file_path that exists */
        if (stat(command, &buffer) == 0)
        {
            return (command);
        }
        return (NULL);
    }
    return (NULL);
}

void execmd(char **argv)
{
    pid_t pid;

    if (argv)
    {
        /* fork a new process */
        pid = fork();
        if (pid < 0) 
        {
            perror("Error: Fork failed");
        }
        else if (pid == 0) 
        {
            /* this is the child process */
            /* execute the actual command with execve */
            char *command = argv[0];
            char *actual_command = get_location(command);
            if (actual_command == NULL)
            {
                printf("%s: command not found\n", command);
                exit(1);
            }
            if (execve(actual_command, argv, NULL) == -1)
            {
                perror("Error:");
                exit(1);
            }
        }
        else 
        {
            /* this is the parent process */
            /* wait for the child process to finish */
            wait(NULL);
            return;
        }
    }
}


