/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:26:32 by jmarks            #+#    #+#             */
/*   Updated: 2023/07/19 15:26:36 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_heredoc(int pipefd[2], char *delimiter)
{
	char	*curr_line;
	pid_t	pid;

	curr_line = NULL;
	if (pipe(pipefd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			curr_line = readline("heredoc> ");
			if (ft_strcmp(curr_line, delimiter) == 0)
			{
				break ;
			}
			write(pipefd[1], curr_line, ft_strlen(curr_line));
			write(pipefd[1], "\n", 1);
			free(curr_line);
		}
		free(curr_line);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
}

void	do_heredoc(int pipefd[2])
{
	char	buffer[MAX_BUFFER];
	ssize_t	nbytes;
	pid_t	pid;

	pid = 0;
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	nbytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
	close(pipefd[0]);
	if (nbytes > 0)
	{
		buffer[nbytes] = '\0';
		printf("%s", buffer);
	}
}

int	input_heredoc(char *delimiter)
{
	int	pipefd[2];

	get_heredoc(pipefd, delimiter);
	do_heredoc(pipefd);
	return (0);
}
