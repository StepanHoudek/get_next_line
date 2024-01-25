/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/25 14:59:48 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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


	// If no characters in buffer
	// 		read the buffer_size from the file and store in buffer
	// If EOF in buffer
	// {
	// create a substring from the buffer from start to EOF
	// return substring
	// }
	// Else if \n in buffer
	// {
	// create a substring from the buffer from start to \n
	// Move buffer forward just after the \n
	// return substring
	// }
	// else
	//
	// recursively call get_next_line

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*buffer_backup;
	size_t		buffer_size;
	ssize_t		bytes_read;

	buffer_size = 200;
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * buffer_size);
		if (!buffer)
			return (0);
	}
	if (*buffer == '\0')
		bytes_read = read(fd, buffer, buffer_size);
	if (bytes_read != buffer_size)
	{
		return (ft_substr(buffer, 0, bytes_read));
	}
	if (ft_strchr(buffer, '\n'))
	{
		buffer_backup = buffer;
		buffer = ft_strchr(buffer, '\n');
		return (ft_substr(buffer_backup, 0, ft_strchr(buffer_backup, '\n')
				- buffer_backup));
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
