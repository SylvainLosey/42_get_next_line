/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylvain <sylvain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:32:45 by sylvain           #+#    #+#             */
/*   Updated: 2022/04/16 18:03:50 by sylvain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd) {
	static int	char_read;
	static char	*stash;
	char		*buffer;
	char		*result;
	
	if (fd < 0)
		return (NULL);
	if (!stash) 
	{
		stash = (char *) malloc(BUFFER_SIZE + 4);
		ft_memset(stash, 0, BUFFER_SIZE + 4);
	}
	if (!char_read)
		char_read = BUFFER_SIZE;
	buffer = (char *) malloc(BUFFER_SIZE +4);
	ft_memset(buffer, 0, BUFFER_SIZE + 4);
	while (!contains_char(stash, '\n') && char_read == BUFFER_SIZE)
	{
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read <= 0) break;
		stash = ft_strjoin(stash, buffer);
		ft_memset(buffer, 0, BUFFER_SIZE + 4);
	}
	free(buffer);
	buffer = NULL;

	if (strlen_until_char(stash, 0) == 0) {
		free(stash);
		stash = NULL;
		return (NULL);
	}
	result = copy_until_return_or_end(stash);
	stash = remove_until_return(stash);
	return (result);	
}

/*
*	Copies the characters from source onto a new string up until
*	1. \n if there is one
*   2. \0 otherwise
*/
char	*copy_until_return_or_end(char *source)
{
	char	*result;
	int		length_up_to_return;
	
	length_up_to_return = strlen_until_char(source, '\n');
	result = (char *) malloc(length_up_to_return + 4);
	ft_memset(result, 0, length_up_to_return + 4);
	if (contains_char(source, '\n'))
		ft_strncpy(result, source, length_up_to_return + 1);
	else
		ft_strncpy(result, source, length_up_to_return);
	return (result);
}

/*
*	Creates a new string with the characters up to \n or \0 removed
*/
char	*remove_until_return(char *source)
{
	char	*result;
	int		total_length;
	int		length_up_to_return;
	int		length_after_return;

	total_length = strlen_until_char(source, 0);
	length_up_to_return = strlen_until_char(source, '\n');

	if (contains_char(source, '\n'))
		length_after_return = total_length - length_up_to_return + 2;
	else
		length_after_return = total_length - length_up_to_return;
	result = (char *) malloc(length_after_return + 4);
	ft_memset(result, 0, length_after_return + 4);
	if (contains_char(source, '\n'))
		ft_strncpy(result, source + length_up_to_return + 1, length_after_return);
	else
		ft_strncpy(result, source + length_up_to_return , length_after_return);

	free(source);
	return (result);
}

bool	contains_char(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return true;
		str++;
	}
	return false;
}

// int	main(void) {
// 	char	*result;
// 	int		fd;

// 	fd = open("tests/43_no_nl", O_RDONLY);

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