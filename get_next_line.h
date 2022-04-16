/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylvain <sylvain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:32:47 by sylvain           #+#    #+#             */
/*   Updated: 2022/04/16 18:04:57 by sylvain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

size_t  strlen_until_char(const char *s, const char c);
char	*ft_strjoin(char *s1, char *s2);
char    *ft_strncpy(char *dest, char *src, unsigned int n);
void    *ft_memset(void *b, int c, size_t len);

char	*get_next_line(int fd);
char	*copy_until_return_or_end(char *source);
char	*remove_until_return(char *source);
bool	contains_char(char *str, char c);
