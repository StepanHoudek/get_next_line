/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/29 12:57:53 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 30
#endif

char	*get_buffer(char *buffer, int fd)
{
	char	*buffer_read;
	char	*ptr;

	buffer_read = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	ptr = NULL;
	if (!buffer_read)
		return (NULL);
	while (read(fd, buffer_read, BUFFER_SIZE))
	{
		ptr = buffer;
		buffer = ft_strjoin(buffer, buffer_read);
		free(ptr);
		if (ft_strchr(buffer, '\n'))
		{
			free(buffer_read);
			return (buffer);
		}
	}
	free(buffer_read);
	return (buffer);
}

char	*read_line(char *buffer)
{
	char	*ptr;

	if (*buffer == '\0')
		return (NULL);
	if (ft_strchr(buffer, '\n'))
	{
		ptr = ft_substr(buffer, 0, ft_strchr(buffer, '\n') - buffer + 1);
		// free(buffer);
		return (ptr);
	}
	else
		return (buffer);
}

char	*remove_line(char *buffer)
{
	char	*ptr;
	char	*nptr;

	nptr = ft_strchr(buffer, '\n');
	if (!buffer || *buffer == '\0')
		return (NULL);
	if (*(nptr + 1) == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	else if (nptr)
	{
		ptr = buffer;
		buffer = ft_strjoin(nptr + 1, "");
		free(ptr);
	}
	else
	{
		free(buffer);
		buffer = NULL;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	buffer = get_buffer(buffer, fd);
	if (!buffer)
		return (NULL);
	line = read_line(buffer);
	buffer = remove_line(buffer);
	if (!buffer && !line)
	{
		free(buffer);
		return (NULL);
	}
	return (line);
}

/*
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
*/
// jedna fce plni buffer do \n or EOF
// Dalsi funkce bere z bufferu tu line or EOF a vraci ptr na tu line
// Treti funkce maze line z buffer
