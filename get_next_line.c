/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/25 14:32:35 by shoudek          ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	// If EOF in buffer_ptr
	// {
	// create a substring from the buffer_ptr from start to EOF
	// return substring
	// }
	// Else if \n in buffer_ptr
	// {
	// create a substring from the buffer_ptr from start to \n
	// Move buffer_ptr forward just after the \n
	// return substring
	// }
	// else
	// read the buffer_size from the file and store in buffer
	// recursively call get_next_line
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
