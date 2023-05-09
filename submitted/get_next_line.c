/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:34:01 by dlu               #+#    #+#             */
/*   Updated: 2023/05/09 18:48:44 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/* Get the length of the string. */
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

/* Malloc a string that start at an index for length len. */
char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) + 1)
		len = ft_strlen(s) + 1;
	str = (char *) malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len && start + i < ft_strlen(s))
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}

/* Return the string with the first \n (or \0), and update the ptr to next
 * byte (both copy and free).
 * At the address of prev, str has to include a '\n' at indexi unless it's the end.
 * Return NULL if pointer is NULL or malloc fails. */
static char	*process_next_line(char **prev, int index, int end)
{
	char	*line;
	char	*tmp;

	if (end && !(*prev)[0])
	{
		free(*prev);
		*prev = NULL;
		return (NULL);
	}
	if (!end || (*prev)[index] == '\n')
	{
		line = ft_substr(*prev, 0, index + 1);
		tmp = ft_substr(*prev, index + 1, ft_strlen(*prev) - index - 1);
		free(*prev);
		*prev = tmp;
	}
	else
	{
		line = ft_substr(*prev, 0, index);
		free(*prev);
		*prev = NULL;
	}
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

static int	prev_init(char **prev)
{
	*prev = (char *) malloc(sizeof(char));
	if (!*prev)
		return (0);
	(*prev)[0] = '\0';
	return (1);
}

int	nl_index(char *prev, int end)
{
	int	i;

	if (!prev)
		return (-1);
	i = -1;
	while (prev[++i])
		if (prev[i] == '\n')
			return (i);
	if (end)
		return (i);
	else
		return (-1);
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
		if (read_bytes < 0)
		{
			free(prev);
			prev = NULL;
			return (NULL);
		}
		append_buffer(&prev, buffer, read_bytes);
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
