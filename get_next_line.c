/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylvain <sylvain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:32:45 by sylvain           #+#    #+#             */
/*   Updated: 2022/04/15 16:50:04 by sylvain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		contains_no_return(char *str)
{
	while (*str++)
		if (*str == '\n') return (0);
	return (1);
}

char	*copy_until_return(char *str, bool is_last_read)
{
	char	*result;
	int		total_length;
	int		length_up_to_return;

	total_length = ft_strlen(str);
	length_up_to_return = ft_strlen_return(str);
	if (length_up_to_return == total_length && is_last_read)
		return (str);
	result = (char *) malloc(sizeof(char) * (length_up_to_return+2));
	ft_strlcpy(result, str, length_up_to_return+2);
	return (result);
}

char	*remove_until_return(char *str, bool is_last_read)
{
	char	*result;
	int		total_length;
	int		length_up_to_return;

	length_up_to_return = ft_strlen_return(str);
	total_length = ft_strlen(str);
	if (length_up_to_return == total_length && is_last_read)
	{
		result = (char *) malloc(sizeof(char));
		*result = '\0';
		return (result);
	}
	result = (char *) malloc(sizeof(char) * (total_length-length_up_to_return ));
	ft_strlcpy(result, str + length_up_to_return + 1, total_length-length_up_to_return);
	free(str);
	return (result);
}

char	*get_next_line(int fd) {
	static char	*stash;
	static int	char_read;

	char		*buffer;
	char		*result;
	
	if (!stash)
		stash = (char *) malloc(sizeof(char));
	if (!char_read)
		char_read = BUFFER_SIZE;
	buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	while (contains_no_return(stash) && char_read == BUFFER_SIZE)
	{
		char_read = read(fd, buffer, BUFFER_SIZE);
		stash = ft_strjoin(stash, buffer);
	}
	if (char_read < BUFFER_SIZE && ft_strlen(stash) == 0) {
		free(stash);
		return (NULL);

	}
	// free(buffer);
	result = copy_until_return(stash, char_read < BUFFER_SIZE);
	stash = remove_until_return(stash, char_read < BUFFER_SIZE);
	return (result);	
}

// int	main(void) {
// 	char	*result;
// 	int		fd;

// 	fd = open("tests/hello.txt", O_RDONLY);

// 	result = (char *) malloc(sizeof(char));
// 	*result = 'a';
// 	while (result)
// 	{
// 		result = get_next_line(fd);
// 		printf("%s", result);
// 	}
// 	return (0);
// }