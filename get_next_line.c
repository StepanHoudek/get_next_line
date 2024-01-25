/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/25 12:09:03 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	g_buff_size = 1024;
static char	*buffer;

char	*get_next_line(int fd)
{
	char	*buff;
	char	*ptr;
	int		j;
	int		bytes_read;
	int		i;

	buff = malloc(sizeof(char) * g_buff_size);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	i = 0;
	while (bytes_read && *(buff++) != '\n')
	{
		bytes_read = read(fd, buff, 1);
		if (bytes_read != 1)
			return (NULL);
		i++;
	}
	ptr = malloc(sizeof(char) * i);
	if (!ptr)
		return (NULL);
	j = 0;
	while (i > j)
	{
		ptr[j] = buff[j - i];
		j++;
	}
	i++;
	return (ptr);
}

#include <fcntl.h>
#include <stdio.h>

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
