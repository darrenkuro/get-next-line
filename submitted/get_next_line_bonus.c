/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:34:01 by dlu               #+#    #+#             */
/*   Updated: 2023/05/10 02:11:14 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* Free the old prev and update with the replacement ptr and return it. */
static char	*update_prev(char **prev, char *replace)
{
	free(*prev);
	*prev = replace;
	return (*prev);
}

/* Return the next line, and update the prev to next byte (both copy and free).
 * Prev str has to include a '\n' at index, unless it's at the end.
 * Return NULL if any malloc fails, with all allocated resources freed. */
static char	*process_prev(char **prev, int index, int end)
{
	char	*line;
	char	*tmp;

	if (end && !ft_strlen(*prev))
		return (update_prev(prev, NULL));
	if ((*prev)[index] == '\n')
	{
		line = ft_substr(*prev, 0, index + 1);
		tmp = ft_substr(*prev, index + 1, ft_strlen(*prev) - index - 1);
		update_prev(prev, tmp);
		if (!tmp)
			return (free(line), NULL);
	}
	else
	{
		line = ft_substr(*prev, 0, index);
		update_prev(prev, NULL);
	}
	if (!line)
		return (update_prev(prev, NULL));
	return (line);
}

/* Process next line overhead, protect against faulty BUFFER_SIZE (0). */
static char	*process_next_line(int fd, char **prev)
{
	ssize_t	read_bytes;
	char	buffer[BUFFER_SIZE];

	while (nl_index(*prev, 0) < 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (!append_buffer(prev, buffer, read_bytes))
			return (update_prev(prev, NULL));
		if (read_bytes < BUFFER_SIZE)
			return (process_prev(prev, nl_index(*prev, 1), 1));
	}
	return (process_prev(prev, nl_index(*prev, 0), 0));
}

/* Get the next line of a file descriptor. */
char	*get_next_line(int fd)
{
	static char	*prev[FD_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!prev[fd])
	{
		prev[fd] = (char *) malloc(sizeof(char));
		if (!prev[fd])
			return (NULL);
		prev[fd][0] = '\0';
	}
	return (process_next_line(fd, &prev[fd]));
}

/*
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("test.md", O_RDONLY);
	char *test;

	for(int i = 0; i < 2; i++)
	{
		test = get_next_line(fd);
		printf("%s", test);
		free(test);
	}
	close(fd);
}
*/
