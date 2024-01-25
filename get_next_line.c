/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/25 17:04:21 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char		*ptr;
	ssize_t		bytes_read;

	bytes_read = 0;
	if (!buffer)
		buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	buffer_read = ft_calloc(sizeof(char), BUFFER_SIZE);
	bytes_read = read(fd, buffer_read, BUFFER_SIZE);
	if (bytes_read == 0 && *buffer == '\0')
		return (NULL);
	if (bytes_read)
		buffer = ft_strjoin(buffer, buffer_read);
	free(buffer_read);
	if (ft_strchr(buffer, '\n'))
	{
		ptr = buffer;
		buffer = ft_strchr(buffer, '\n') + 1;
		return (ft_substr(ptr, 0, ft_strchr(ptr, '\n') - ptr + 1));
	}
	else
		get_next_line(fd);
	return (NULL);
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

