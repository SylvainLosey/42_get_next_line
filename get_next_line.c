/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylvain <sylvain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:32:45 by sylvain           #+#    #+#             */
/*   Updated: 2022/04/02 18:56:15 by sylvain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		contains_no_return(char *str)
{
	while (*str++)
		if (*str == '\n') return (0);
	return (1);
}

char	*copy_until_return(char *str)
{
	char	*result;
	int		len;

	len = ft_strlen_return(str);
	result = (char *) malloc(sizeof(char) * (len+1));
	ft_strlcpy(result, str, len+1);
	return (result);
}

char	*get_next_line(int fd) {
	char	*stash;
	char	*buffer;
	
	stash = (char *) malloc(sizeof(char));
	*stash = '\0';
	
	buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	while (contains_no_return(stash))
	{
		read(fd, buffer, BUFFER_SIZE);
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (copy_until_return(stash));	
}

int	main(void) {
	int	fd;

	fd = open("tests/hello.txt", O_RDONLY);

	printf("%s", get_next_line(fd));
	return (0);
}