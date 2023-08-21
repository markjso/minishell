/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:24:51 by abaker            #+#    #+#             */
/*   Updated: 2022/03/30 16:23:28 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAKS_H
# define LEAKS_H

# include <stdlib.h>
# include <sys/types.h>

# define malloc(X) malloc_track(X, __FILE__, __LINE__, __FUNCTION__)
# define free(X) free_track(X)

void	*malloc_track(size_t size, const char *file, int line, const char *func);
void	free_track(void *p);
void	check_leaks(void);

#endif