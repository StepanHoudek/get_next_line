/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:13:41 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/25 17:02:21 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

// cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 *.c ./test/main.c && ./a.out

#include <stdio.h>

void	print_string_fd(int fd, char *line)
{
	line = get_next_line(fd);
	printf("Line: |%s|\n", line);
	free(line);
}

int	main(void)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
		write(2, "Problem opening file.", 21);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	close(fd);
	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
		write(2, "Problem opening file.", 21);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	close(fd);
	return (0);
}
