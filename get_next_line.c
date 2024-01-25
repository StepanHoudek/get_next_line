/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:03:36 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/24 16:03:36 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	
}


#include <stdio.h>
#include <fcntl.h>

int main(void) {
    int file_descriptor;

    // Open a file
    file_descriptor = open("example.txt", O_RDONLY);

    if (file_descriptor == -1) {
        perror("Error opening file");
    } else {
        printf("File descriptor for example.txt: %d\n", file_descriptor);

        // Close the file
        close(file_descriptor);
    }

    return 0;
}
