/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylvain <sylvain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:32:45 by sylvain           #+#    #+#             */
/*   Updated: 2022/04/16 20:01:10 by sylvain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*result;

	if (fd < 0)
		return (NULL);
	stash = get_stash(fd, stash);
	if (!stash)
		return (NULL);
	result = copy_until_return_or_end(stash);
	stash = remove_until_return(stash);
	return (result);
}

char	*get_stash(int fd, char *stash)
{
	char	*buffer;

	buffer = ft_calloc(1, (BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!contains_char(stash, '\n'))
	{
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
			break ;
		stash = ft_strjoin(stash, buffer);
		ft_bzero(buffer, (BUFFER_SIZE + 1) * sizeof(char));
	}
	free(buffer);
	if (!stash || strlen_until_char(stash, 0) == 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

/*
*	Copies the characters from source onto a new string up until
*	1. \n if there is one
*   2. \0 otherwise
*/
char	*copy_until_return_or_end(char *source)
{
	char	*result;
	int		len_up_to_return;

	len_up_to_return = strlen_until_char(source, '\n');
	result = (char *) ft_calloc(1, len_up_to_return + 4);
	if (contains_char(source, '\n'))
		ft_strncpy(result, source, len_up_to_return + 1);
	else
		ft_strncpy(result, source, len_up_to_return);
	return (result);
}

/*
*	Creates a new string with the characters up to \n or \0 removed
*/
char	*remove_until_return(char *source)
{
	char	*result;
	int		total_length;
	int		len_up_to_return;
	int		len_after_return;

	total_length = strlen_until_char(source, 0);
	len_up_to_return = strlen_until_char(source, '\n');
	if (contains_char(source, '\n'))
		len_after_return = total_length - len_up_to_return + 2;
	else
		len_after_return = total_length - len_up_to_return;
	result = (char *) ft_calloc(1, len_after_return + 4);
	if (contains_char(source, '\n'))
		ft_strncpy(result, source + len_up_to_return + 1, len_after_return);
	else
		ft_strncpy(result, source + len_up_to_return, len_after_return);
	free(source);
	return (result);
}

bool	contains_char(char *str, char c)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

// int	main(void) {
// 	char	*result;
// 	int		fd;

// 	fd = open("tests/empty", O_RDONLY);

// 	result = (char *) malloc(sizeof(char));
// 	*result = 'a';
// 	while (result)
// 	{
// 		result = get_next_line(fd);
// 		printf("%s", result);
// 	}
// 	free(result);
// 	// getchar();
// 	return (0);
// }