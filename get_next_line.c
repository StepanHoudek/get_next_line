/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/25 16:37:35 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (s[0] != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (s[0] == (unsigned char)c)
	{
		return ((char *)s);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		size++;
		s++;
	}
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	if ((size_t)start + len > ft_strlen(s))
		len = ft_strlen(s) - (size_t)start;
	if ((size_t)start >= ft_strlen(s))
	{
		substr = malloc(sizeof(char));
		if (!substr)
			return (0);
		substr[0] = 0;
		return (substr);
	}
	substr = malloc(sizeof(char) * len + 1);
	if (!substr)
		return (0);
	i = 0;
	while (s[i + start] != '\0' && i < (unsigned int)len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1len + s2len) + 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

// If no characters in buffer
// 	read the buffer_size from the file and store in buffer
// If EOF in buffer
// {
// 	create a substring from the buffer from start to EOF
// 	return substring
// 	}
// Else if \n in buffer
// 	{
// 	create a substring from the buffer from start to \n
// 	Move buffer forward just after the \n
// 	return substring
// 	}
// else
// 	recursively call get_next_line

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*buffer_read;
	char		*buffer_ptr;
	ssize_t		bytes_read;

	bytes_read = 0;
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE);
		if (!buffer)
			return (0);
	}
	buffer_read = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer_read)
		return (0);
	bytes_read = read(fd, buffer_read, BUFFER_SIZE);
	if (bytes_read == 0 && *buffer == '\0')
		return (NULL);
	if (bytes_read)
		buffer = ft_strjoin(buffer, buffer_read);
	if (ft_strchr(buffer, '\n'))
	{
		buffer_ptr = buffer;
		buffer = ft_strchr(buffer, '\n') + 1;
		return (ft_substr(buffer_ptr, 0, ft_strchr(buffer_ptr, '\n')
				- buffer_ptr + 1));
	}
	else
		get_next_line(fd);
}

int	main(void)
{
	char	*path;
	int		fd;
	char	*ptr;

	path = "example.txt";
	fd = open(path, O_RDONLY);
	ptr = get_next_line(fd);
	printf("%s", ptr);
	while (ptr)
	{
		ptr = get_next_line(fd);
		printf("%s", ptr);
	}
}
