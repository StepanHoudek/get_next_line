/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/26 17:45:15 by shoudek          ###   ########.fr       */
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

	buffer_read = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	ptr = NULL;
	if (!buffer_read)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc(sizeof(char), 1);
		if (!buffer)
			return (NULL);
	}
	while (read(fd, buffer_read, BUFFER_SIZE))
	{
		buffer_read[ft_strlen(buffer_read)] = '\0';
		ptr = buffer;
		buffer = ft_strjoin(buffer, buffer_read);
		free(ptr);
		if (ft_strchr(buffer, '\n'))
			return (buffer);
	}
	return (buffer);
}

char	*read_line(char *buffer)
{
	char	*ptr;

	if (ft_strchr(buffer, '\n'))
	{
		ptr = ft_substr(buffer, 0, ft_strchr(buffer, '\n') - buffer + 1);
		free(buffer);
		return (ptr);
	}
	else
		return (buffer);
}

char	*remove_line(char *buffer)
{
	buffer = ft_strchr(buffer, '\n') + 1;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	buffer = get_buffer(buffer, fd);
	line = read_line(buffer);
	buffer = remove_line(buffer);
	return (line);
}

// char	*get_next_line(int fd)
// {
// 	static char	*buffer;
// 	char		*buffer_read;
// 	char		*ptr;
// 	ssize_t		bytes_read;

// 	bytes_read = 0;
// 	buffer_read = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
// 	// adding +1 for null to BUFFER_SIZE, TO-DO to put the null there
// 	ptr = NULL;
// 	if (!buffer_read)
// 		return (NULL);
// 	if (!buffer)
// 	{
// 		buffer = ft_calloc(sizeof(char), 1);
// 		if (!buffer)
// 			return (NULL);
// 	}
// 	bytes_read = read(fd, buffer_read, BUFFER_SIZE);
// 	while (bytes_read > 0)
// 	{
// 		buffer = ft_strjoin(buffer, buffer_read); // HERE, free old buffer
// 		if (ft_strchr(buffer, '\n'))
// 		{
// 			ptr = buffer;
// 			buffer = ft_strchr(buffer, '\n') + 1;
// 			free(buffer_read);
// 			// Gotta malloc buffer again. Free ptr;
// 			return (ft_substr(ptr, 0, ft_strchr(ptr, '\n') - ptr + 1));
// 		}
// 		bytes_read = read(fd, buffer_read, BUFFER_SIZE);
// 	}
// 	// END OF FILE PRINT REMAINING BUFFER
// 	free(buffer_read);
// 	if (ptr)
// 		free(ptr);
// 	return (NULL);
// }

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
