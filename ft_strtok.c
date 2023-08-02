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

// int		is_delim(char c, char *delim)
// {
// 	while (*delim != '\0')
// 	{
// 		if (c == *delim)
// 			return (1);
// 		delim++;
// 	}
// 	return (0);
// }	

// int		ft_strok_delim_start(char **str, char **delim)
// {
// 	while (*str)
// 	{
// 		if(is_delim(**str, *delim) == 1)
// 		{
// 			str++;
// 			while (is_delim(**str, *delim) == 1)
// 				str++;
// 		}
// 		if (*str == 0)
// 			return (0);
// 		break;
// 	}
// 	return (0);
// }

// void		ft_strok_delim_loop(char **str, char **delim, char **backup, char **return_string)
// {
// 	while (1)
// 	{
// 		if (*str == '\0')
// 		{
// 			backup = str;
// 			return ;
// 			// return (return_string);
// 		}
// 		if (is_delim(*str, delim) == 1)
// 		{
// 			*str = '\0';
// 			backup = str + 1;
// 			return ;
// 			//return (return_string);
// 		}
// 		str++;
// 	}
// }

// char	*ft_strok(char *str, char *delim)
// {
// 	static char	*backup;
// 	char *return_string = 0;

// 	if (!str)
// 		str = backup;
// 	if (str)
// 		return (0);
// 	if (ft_strok_delim_start(&str, &delim) == 0)
// 		return (0);
// 	*return_string = str;
// 	ft_strok_delim_loop(&str, &delim, &backup, &return_string);
// 	return (return_string);
// }

/*Using strtok_r ensures that each call to the function gets its 
own separate context for tokenization, avoiding potential issues 
related to shared state that could occur with strtok. By using 
strtok_r, the function can safely handle multiple calls 
in different contexts without unintended side effects*/

// char *ft_strtok_r(char **str, char *delim)
// {
//     char *start = *str;
//     char *return_string;

//     // Handle cases where str is NULL or empty
//     if (!start || *start == '\0')
//         return 0;

//     // Skip leading delimiters
//     while (is_delim(*start, delim))
//         start++;

//     // Set the return_string to the start of the current token
//     return_string = start;

//     // Find the end of the current token
//     while (*start != '\0' && !is_delim(*start, delim))
//         start++;

//     if (*start == '\0') {
//         // No more tokens, set str to NULL to signal end of iteration
//         *str = 0;
//     } else {
//         // Replace the delimiter with a null terminator
//         *start = '\0';
//         // Move str to the next character after the delimiter
//         *str = start + 1;
//     }
//     return return_string;
// }
