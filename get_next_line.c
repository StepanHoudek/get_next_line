/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/26 17:27:03 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*get_buffer(char *buffer, int fd)
{
	char	*buffer_read;
	char	*ptr;
	ssize_t	bytes_read;

	bytes_read = 0;
	buffer_read = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	// adding +1 for null to BUFFER_SIZE, TO-DO to put the null there
	ptr = NULL;
	if (!buffer_read)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc(sizeof(char), 1);
		if (!buffer)
			return (NULL);
	}
	bytes_read = read(fd, buffer_read, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		ptr = buffer;
		buffer = ft_strjoin(buffer, buffer_read); // HERE, free old buffer
		free(ptr);
		if (ft_strchr(buffer, '\n'))
		{
			ptr = buffer;
			buffer = ft_strchr(buffer, '\n') + 1;
			free(buffer_read);
			// Gotta malloc buffer again. Free ptr;
			return (ft_substr(ptr, 0, ft_strchr(ptr, '\n') - ptr + 1));
		}
		bytes_read = read(fd, buffer_read, BUFFER_SIZE);
	}
}

char	*read_line(char *buffer)
{
	return (NULL);
}

char	*remove_line(char *buffer)
{
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*buffer_read;
	char		*ptr;
	ssize_t		bytes_read;

	bytes_read = 0;
	buffer_read = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	// adding +1 for null to BUFFER_SIZE, TO-DO to put the null there
	ptr = NULL;
	if (!buffer_read)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc(sizeof(char), 1);
		if (!buffer)
			return (NULL);
	}
	bytes_read = read(fd, buffer_read, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer = ft_strjoin(buffer, buffer_read); // HERE, free old buffer
		if (ft_strchr(buffer, '\n'))
		{
			ptr = buffer;
			buffer = ft_strchr(buffer, '\n') + 1;
			free(buffer_read);
			// Gotta malloc buffer again. Free ptr;
			return (ft_substr(ptr, 0, ft_strchr(ptr, '\n') - ptr + 1));
		}
		bytes_read = read(fd, buffer_read, BUFFER_SIZE);
	}
	// END OF FILE PRINT REMAINING BUFFER
	free(buffer_read);
	if (ptr)
		free(ptr);
	return (NULL);
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
