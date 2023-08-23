/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:24:45 by abaker            #+#    #+#             */
/*   Updated: 2022/03/30 16:28:38 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct leaks Leaks;

struct leaks{
	void		*ptr;
	const char	*file;
	int			line;
	const char	*func;
	size_t		size;
	Leaks		*next;
};

static Leaks	*g_leaks = NULL;

static Leaks	*new_leak(void *ptr, const char *file, int line, const char *func, size_t size)
{
	Leaks	*new = calloc(1, sizeof(*new));

	if (!new)
		return (NULL);
	new->ptr = ptr;
	new->file = file;
	new->line = line;
	new->func = func;
	new->size = size;
	return (new);
}

static void	add_leak(Leaks *new)
{
	Leaks	*curr = g_leaks;

	if (!new)
		return ;
	if (!g_leaks)
		g_leaks = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

static void	remove_leak(void *ptr)
{
	Leaks	*curr = g_leaks, *prev = NULL;

	if (!ptr || !g_leaks)
		return ;
	while (curr && curr->ptr != ptr)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr)
	{
		if (!prev)
			g_leaks = curr->next;
		else
			prev->next = curr->next;
		free(curr);
	}
}

static void	free_leaks(void)
{
	Leaks	*next;

	while (g_leaks)
	{
		next = g_leaks->next;
		free(g_leaks->ptr);
		free(g_leaks);
		g_leaks = next;
	}
}

static bool	malloc_match(Leaks *l1, Leaks *l2)
{
	return (strcmp(l1->file, l2->file) == 0 && l1->line == l2->line);
}

static bool	first_occurance(Leaks *leak)
{
	Leaks	*curr = g_leaks;

	if (!leak || !g_leaks)
		return (false);
	while (curr && curr != leak)
	{
		if (malloc_match(curr, leak))
			return (false);
		curr = curr->next;
	}
	return (true);
}

static int	count_leaks(Leaks *leak)
{
	Leaks	*curr = g_leaks;
	int		i = 0;

	while (curr)
	{
		if (malloc_match(curr, leak))
			i++;
		curr = curr->next;
	}
	return (i);
}

void	*malloc_track(size_t size, const char *file, int line, const char *func)
{
	void	*ptr = malloc(size);

	add_leak(new_leak(ptr, file, line, func, size));
	return (ptr);
}

void	free_track(void *ptr)
{
	remove_leak(ptr);
	free(ptr);
}

void	check_leaks(void)
{
	Leaks	*curr = g_leaks;

	if (!curr)
	{
		printf("\e[92mAll Malloc Calls have been freed\n\e[0m");
		return ;
	}
	while (curr)
	{
		if (first_occurance(curr))
			printf("\e[91mMalloc in File: \e[93m%s\e[91m on line: \e[93m%i\e[91m in Func: \e[93m%s\e[91m has leaked a total of \e[93m%i\e[91m times!\n\n\e[0m",
				curr->file, curr->line, curr->func, count_leaks(curr));
		curr = curr->next;
	}
	free_leaks();
}