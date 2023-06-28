/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:47:22 by jchurch           #+#    #+#             */
/*   Updated: 2023/06/27 15:00:13 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}	

int		ft_strok_delim_start(char **str, char **delim)
{
	while (*str != '\0')
	{
		if(is_delim(*str, delim) == 1)
		{
			str++;
			while (is_delim(*str, delim) == 1)
				str++;
		}
		if (*str == '\0')
			return (0);
		break;
	}
}

void		ft_strok_delim_loop(char **str, char **delim, char **backup, char **return_string)
{
	while (1)
	{
		if (*str == '\0')
		{
			backup = str;
			return ;
			// return (return_string);
		}
		if (is_delim(*str, delim) == 1)
		{
			*str = '\0';
			backup = str + 1;
			return ;
			//return (return_string);
		}
		str++;
	}
}

char	*ft_strok(char *str, char *delim)
{
	static char	*backup;
	char *return_string;

	if (!str)
		str = backup;
	if (str)
		return (0);
	if (ft_strok_delim_start(&str, &delim) == 0)
		return (0);
	*return_string = str;
	ft_strok_delim_loop(&str, &delim, &backup, &return_string);
	return (return_string);
}
