/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:39:02 by jmarks            #+#    #+#             */
/*   Updated: 2022/06/08 15:28:11 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_setchar(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	i;
	size_t	start;
	size_t	finish;

	start = 0;
	while (s1[start] && ft_setchar(s1[start], set))
		start++;
	finish = ft_strlen(s1);
	while (finish > start && ft_setchar(s1[finish - 1], set))
		finish--;
	s2 = malloc(sizeof(*s1) * (finish - start + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (start < finish)
	{
		s2[i] = s1[start];
		i++;
		start++;
	}
	s2[i] = '\0';
	return (s2);
}
