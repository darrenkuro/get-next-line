/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:34:01 by dlu               #+#    #+#             */
/*   Updated: 2023/05/08 19:23:10 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

/* Return the string with the first \n (or \0), and update the ptr to next
 * byte (both copy and free).
 * At the address of prev, str has to include a '\n' or '\0' at index.
 * Return NULL if pointer is NULL or malloc fails. */
static char	*process_next_line(char **prev, int index)
{
	char	*line;
	char	*tmp;
	int		i;

	if (!*prev)
		return (NULL);
	printf("1st malloc: %d\n", index + 2);
	line = (char *) malloc((index + 2) * sizeof(char));
	printf("2nd malloc: %d\n", ft_strlen(*prev) - index);
	tmp = (char *) malloc((ft_strlen(*prev) - index) * sizeof(char));
	if (!line || !tmp)
		return (NULL);
	i = -1;
	while (++i <= index)
		line[i] = (*prev)[i];
	line[i--] = '\0';
	while (++i < ft_strlen(*prev))
		tmp[i - index - 1] = (*prev)[i];
	printf("null intex: %d\n", i - index - 1);
	tmp[i - index - 1] = '\0';
	free(*prev);
	*prev = tmp;
	printf("%c\n", tmp[0]);
	return (line);
}

/*
char	*get_next_line(int fd)
{
	static char	*prev;
	ssize_t		read_bytes;
	char		buffer[BUFFER_SIZE];

	if (fd < 0)
		return (NULL);
	//return (process_next_line(fd, prev));
	while (get_nl_index(prev, read_bytes) < 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		append_buffer(&prev, buffer, read_bytes);
	}
}
*/

int	main(void)
{
	char	*test;
	char	*line;

	test = (char *) malloc(6);
	test[0] = 'a';
	test[1] = 'b';
	test[2] = '\n';
	test[3] = 'c';
	test[4] = 'd';
	test[5] = '\0';
	line = process_next_line(&test, 2);
	printf("left: %s\n", test);
	printf("line: %s\n", line);
	free(test);
	free(line);
	return (0);
}
