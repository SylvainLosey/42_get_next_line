/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylvain <sylvain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:32:43 by sylvain           #+#    #+#             */
/*   Updated: 2022/04/16 19:59:00 by sylvain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	strlen_until_char(const char *s, const char c)
{
	size_t	i;

	i = 0;
	if (c == 0)
	{
		while (s[i])
			i++;
	}
	else
	{
		while (s[i] && s[i] != c)
			i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (!s1)
		s1 = (char *) ft_calloc(1, 1 * sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	len1 = strlen_until_char(s1, 0);
	len2 = strlen_until_char(s2, 0);
	str = (char *) malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2[++i])
		str[len1++] = s2[i];
	str[len1] = '\0';
	free(s1);
	return (str);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

void	ft_bzero(void *b, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	dest = b;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}
