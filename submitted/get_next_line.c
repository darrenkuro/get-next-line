/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:34:01 by dlu               #+#    #+#             */
/*   Updated: 2023/05/09 21:33:17 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	prev_init(char **prev)
{
	*prev = (char *) malloc(sizeof(char));
	if (!*prev)
		return (0);
	(*prev)[0] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*prev;
	ssize_t		read_bytes;
	char		buffer[BUFFER_SIZE];

	if (fd < 0 || (!prev && !prev_init(&prev)))
		return (NULL);
	while (nl_index(prev, 0) < 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (!append_buffer(&prev, buffer, read_bytes))
		{
			free(prev);
			prev = NULL;
			return (NULL);
		}
		if (read_bytes < BUFFER_SIZE)
			return (process_next_line(&prev, nl_index(prev, 1), 1));
	}
	return (process_next_line(&prev, nl_index(prev, 0), 0));
}
/*
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int	main(void)
{
	char	*line;
	int	fd = open("test.md", O_RDONLY);

	for (int i = 0; i < 4; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
