/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:34:01 by dlu               #+#    #+#             */
/*   Updated: 2023/05/09 00:04:28 by dlu              ###   ########.fr       */
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
	int		len;

	len = ft_strlen(*prev);
	line = (char *) malloc((index + 2) * sizeof(char));
	tmp = (char *) malloc((len - index) * sizeof(char));
	if (!line || !tmp)
		return (NULL);
	i = -1;
	while (++i <= index)
		line[i] = (*prev)[i];
	line[i--] = '\0';
	while (++i < len)
		tmp[i - index - 1] = (*prev)[i];
	tmp[i - index - 1] = '\0';
	free(*prev);
	*prev = tmp;
	return (line);
}

static char	*process_last_line(char **prev, char *buffer)
{
	char	*line;
	int		i;

	line = (char *) malloc(ft_strlen(buffer) + 1 * sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (buffer[++i])
		line[i] = buffer[i];
	line[i]  = '\0';
	free(*prev);
	return (line);
}

static void	append_buffer(char **prev, char *buffer, ssize_t n)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	if (n < 0)
		return ;
	len = ft_strlen(*prev);
	tmp = (char *) malloc((len + n + 1) * sizeof(char));
	if (!tmp)
		return ;
	i = -1;
	while (++i < len)
		tmp[i] = (*prev)[i];
	j = -1;
	--i;
	while (--n >= 0)
		tmp[++i] = buffer[++j];
	tmp[++i] = '\0';
	free(*prev);
	*prev = tmp;
}

static void	prev_init(char **prev)
{
	*prev = (char *) malloc(sizeof(char));
	if (!*prev)
		return ;
	(*prev)[0] = '\0';
}

int	get_nl_index(char *prev, ssize_t read_bytes)
{
	int	i;

	i = -1;
	while (prev[++i])
		if (prev[i] == '\n')
			return (i);
	return (-1);

}

char	*get_next_line(int fd)
{
	static char	*prev;
	ssize_t		read_bytes;
	char		buffer[BUFFER_SIZE];
	int			index;

	if (!prev)
		prev_init(&prev);
	if (fd < 0 || !prev)
		return (NULL);
	index = -1;
	while (index < 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			return (NULL);
		append_buffer(&prev, buffer, read_bytes);
		index = get_nl_index(prev, read_bytes);
		printf("index: %d\n", index);
		if (read_bytes < BUFFER_SIZE && index < 0)
			return (process_last_line(&prev, buffer));
	}
	return (process_next_line(&prev, index));
}

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int	main(void)
{
	char	*line;
	int	fd = open("test.md", O_RDONLY);
	
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	close(fd);
	/*
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
	//printf("left: %s\n", test);
	//printf("line: %s\n", line);
	//free(test);
	free(line);
	append_buffer(&test, "abcd", 2);
	printf("%s\n", test);
	free(test);
	*/
	return (0);
}
