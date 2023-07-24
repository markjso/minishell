/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:00:49 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/27 15:00:51 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program g_program;

void	remove_redirect_tokens(t_token_list **root, t_token_list *delete_me)
{
	t_token_list	*next_token;

	next_token = delete_me->next;
	ll_remove_node(root, delete_me);
	ll_remove_node(root, next_token);
}


/*
If either STDOUT_FILENO or STDIN_FILENO where modified:
Reset to defualt. 
*/
void	remove_redirect()
{
	if (g_program.out_file > 0)
	{
		close(g_program.out_file);
		dup2(g_program.out_backup, STDOUT_FILENO);
		close(g_program.out_backup);
	}
	if (g_program.in_file > 0)
	{
		close(g_program.in_file);
		dup2(g_program.in_backup, STDIN_FILENO);
		close(g_program.in_backup);
	}
	
}

int std_output()
{
	debugFunctionName("STD_OUT");
	char			*file;
	int				file_temp;
	// t_token_list	*temp_token;

	file = ft_strdup(g_program.redirect_out); // Malloc freed
	printf("file: %s\n", file);
	file_temp = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (file_temp == -1)
		perror("Error in std_input: \n");
	printf("tempfile number: %d\n", file_temp);
	g_program.out_backup = dup(STDOUT_FILENO);
	printf("backup number: %d\n", g_program.out_backup);
	g_program.out_file = dup2(file_temp, STDOUT_FILENO);
	close(file_temp);
	printf("outfile number: %d\n", g_program.out_file);
	return (0);
}

int std_input(t_token_list **root, t_token_list *curr)
{
	debugFunctionName("STD_IN");
	int				file_temp;
	char			*file;
	t_token_list	*temp_token;

	file = ft_strdup(g_program.redirect_in); // MALLOC freed
	file_temp = open(file, O_RDONLY, 0444);
	free(file); //FREE
	if (file_temp == -1)
		perror("Error in std_input: \n");
	g_program.in_backup = dup(STDIN_FILENO);
	g_program.in_file = dup2(file_temp, STDIN_FILENO);
	close(file_temp);
	temp_token = curr;
	curr = curr->next->next; // Skip arrow < and name of file
	ll_remove_node(root, temp_token->next); // Delete name of file
	ll_remove_node(root, temp_token); // Delete arrow <
	return (0);
}

void output_append(t_token_list **root, t_token_list *curr)
{
	debugFunctionName("STD_APPEND");
	char			*file;
	int				file_temp;
	t_token_list	*temp_token;

	file = ft_strdup(g_program.redirect_out); // Malloc
	file_temp =open(file, O_CREAT | O_WRONLY | O_APPEND , 0644);
	free(file);
	if (file_temp == -1)
		perror("Error in std_append: \n");
	g_program.out_backup = dup(STDOUT_FILENO);
	g_program.out_file = dup2(file_temp, STDOUT_FILENO);
	close(file_temp);
	temp_token = curr;
	curr = curr->next->next; // Skip arrow < and name of file
	ll_remove_node(root, temp_token->next); // Delete name of file
	ll_remove_node(root, temp_token); // Delete arrow <	return (0);
}

void get_heredoc(int pipefd[2], char *delimiter)
{
    char *curr_line;
    pid_t pid;

	curr_line = NULL;
    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        exit(2);
    }

    pid = fork();
    if (pid == 0) // CHILD PROCESS
	{ 
        close(pipefd[0]); // Close read end in child process so that it will write

        while (1) // start a loop to read input from user
		{
            curr_line = readline("heredoc> "); //displays the prompt heredoc> and stores it in curr_line
            if (ft_strcmp(curr_line, delimiter) == 0) // checks to see if the delimiter is the line and if so breaks
			{
                break;
            }
            write(pipefd[1], curr_line, ft_strlen(curr_line)); // write curr_line to the write end of the pipe
            write(pipefd[1], "\n", 1);
            free(curr_line);
        }
        free(curr_line);
        close(pipefd[1]); // close the write end of the pipe in the child process. Ends writing to the pipe.
        exit(EXIT_SUCCESS); // child process ends
    }
}

void do_heredoc(int pipefd[2])
{
    char buffer[MAX_BUFFER]; // store the data read from the pipe
    ssize_t nBytes; // store the number of bytes read from the pipe
	pid_t pid;

	pid = 0;
    close(pipefd[1]); // Close write end in parent process. The parenet will only read
    waitpid(pid, NULL, 0); // wait for the child process to finish. May not be used.

    nBytes = read(pipefd[0], buffer, sizeof(buffer) - 1); // reads data from the read end into buffer
    close(pipefd[0]); // closes the read end

    if (nBytes > 0)
	{
        buffer[nBytes] = '\0';
        printf("%s", buffer); // prints the contents of buffer to the console
    }
}

int input_heredoc(char *delimiter)
{
    int pipefd[2];

    get_heredoc(pipefd, delimiter);
    do_heredoc(pipefd);
    return (0);
}









/*
If a matching close quote is found: 
	Index will be moved to 1 char after the close quote. 

If no matching close quote is found: 
	Index will be moved to 1 char after the current loose quote. 
*/
void	locate_second_quote(char *str)
{
	int		second;

	second = g_program.redirect_index + 1; // One after the quote
	while (str[second] != '\0') // For the length of the string
	{
		if (str[second] == str[g_program.redirect_index]) // If matching quote found
		{
			g_program.redirect_index = second + 1; // Make first be the index of the 2nd quote plus one next outside of the quote. 
			break ; // First will now be one after the matching quote. 
		}
		second++;
	}
	if (str[second] == '\0') // At end and therefore no matching quote was found. 
	{
        g_program.redirect_index++; // One after the current quote. 
        return ; // Can remove this return if norm error. 
	}
}


char	*get_file_name(char *str)
{
	int 	end_of_name;
	char	*file_name;

	g_program.redirect_index++;
	while (ft_is_white_space(str[g_program.redirect_index]))
		g_program.redirect_index++;
	end_of_name = g_program.redirect_index;
	while (ft_is_not_white_space(str[end_of_name]) == 1)
		end_of_name++;	
	file_name = ft_substr(str, g_program.redirect_index, end_of_name - g_program.redirect_index);
	if (file_name)
		return (file_name); // MALLOC
	else
		return (NULL);
}


void	do_redirect(t_token_list **root, t_token_list *curr, int num)
{
    debugFunctionName("DO_REDIR");

	if (curr->next == NULL)
		perror("File not found\n");
	if (num == 1) // >
	{
		g_program.redirect_out = ft_strdup(curr->next->data); // Malloc freed
		std_output();
		free(g_program.redirect_out); // free
	}
	else if (num == 2) // >>
	{
		g_program.redirect_out = ft_strdup(curr->next->data); // Malloc freed
		output_append(root, curr);
		free(g_program.redirect_out); // free
	}
	else if (num == 3)  // <
	{
		g_program.redirect_in = ft_strdup(curr->next->data); //Malloc freed
		std_input(root, curr);
		free(g_program.redirect_in); // free
	}
	else if (num == 4) // <<
	{
		g_program.redirect_in = ft_strdup(curr->next->data);
		input_heredoc(g_program.redirect_in);
	}
}

void	ft_continue(t_token_list **root)
{
	printf("std out is : %s\n", g_program.redirect_out);
	remove_quotes(root);
	copy_into_array(root);			// if it is one of the builtin commands do it. Found in buitlin_utils.c
	if (is_builtin_cmd())
	{
		do_builtins(g_program.token, &g_program);
	}
	else // else it is one of the standard shell commands so execute that with execmd. Found in execmd.c
	{
		execmd(&g_program);
	}
	remove_redirect(); // Reset redirection if changed.
}

void check_for_redirect(t_token_list **root)
{
    debugFunctionName("CHECK_REDIR");
	t_token_list	*curr;
	t_token_list	*temp_token;

	curr = *root;
    while (curr != NULL)
    {
		if (curr == NULL)
			break ;
        if (curr->data[0] == '>')
		{
			do_redirect(root, curr, 1);
			remove_redirect();
			temp_token = curr;
			curr = curr->next->next;
			remove_redirect_tokens(root, temp_token);
			// temp_token = curr;
			// if (curr->next)
			// 	curr = curr->next;
			// ll_remove_node(root, temp_token);
			// if (curr->next)
			// {
			// 	temp_token = curr;
			// 	curr = curr->next;
			// 	ll_remove_node(root, temp_token);
			// }
		}
		else if (curr->data[0] == '>' && curr->data[1] == '>')
			do_redirect(root, curr, 2);
        else if (curr->data[0] == '<')
			do_redirect(root, curr, 3);
		else if (curr->data[0] == '<' && curr->data[1] == '<')
			do_redirect(root, curr, 4);
		if (curr == NULL)
			break ;
        curr = curr->next;
    }
	ft_continue(root);
}
