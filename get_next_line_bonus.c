/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/29 15:43:12 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	if (!buffer || *buffer == '\0')
		return (NULL);
	if (ft_strchr(buffer, '\n'))
	{
		ptr = ft_substr(buffer, 0, ft_strchr(buffer, '\n') - buffer + 1);
		return (ptr);
	}
	else
		return (ft_strjoin(buffer, ""));
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
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = get_buffer(buffer[fd], fd);
	line = read_line(buffer[fd]);
	buffer[fd] = remove_line(buffer[fd]);
	if (!buffer[fd] && !line)
	{
		free(buffer[fd]);
		return (NULL);
	}
	return (line);
}
