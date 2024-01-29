/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/29 14:37:21 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

char	*get_buffer(char *buffer, int fd)
{
	char	*buffer_read;
	char	*ptr;
	int		size;

	buffer_read = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer_read)
		return (NULL);
	size = 1;
	while (size != 0 && ft_strchr(buffer, '\n') == NULL)
	{
		size = read(fd, buffer_read, BUFFER_SIZE);
		if (size == -1)
		{
			free(buffer_read);
			return (NULL);
		}
		buffer_read[size] = '\0';
		ptr = buffer;
		if (ptr == NULL)
			ptr = (char *)ft_calloc(1, 1);
		buffer = ft_strjoin(ptr, buffer_read);
		free(ptr);
	}
	free(buffer_read);
	return (buffer);
}

char	*read_line(char *buffer)
{
	char	*ptr;

	// if (!buffer)
	// 	return (NULL);
	if (*buffer == '\0')
		return (NULL);
	if (ft_strchr(buffer, '\n'))
	{
		ptr = ft_substr(buffer, 0, ft_strchr(buffer, '\n') - buffer + 1);
		return (ptr);
	}
	else
		return (buffer);
}

char	*remove_line(char *buffer)
{
	char	*ptr;

	ptr = ft_strchr(buffer, '\n');
	if (ptr != NULL)
	{
		ptr = ft_strjoin(ptr + 1, "");
		free(buffer);
		return (ptr);
	}
	else
	{
		free(buffer);
		return (NULL);
	}
}


char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_buffer(buffer, fd);
	line = read_line(buffer);
	buffer = remove_line(buffer);
	if (!buffer && !line)
	{
		free(buffer);
		return (NULL);
	}
	return (line);
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

// jedna fce plni buffer do \n or EOF
// Dalsi funkce bere z bufferu tu line or EOF a vraci ptr na tu line
// Treti funkce maze line z buffer
