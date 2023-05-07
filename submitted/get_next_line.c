/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:34:01 by dlu               #+#    #+#             */
/*   Updated: 2023/05/07 17:44:40 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*prev;
	ssize_t		read_bytes;
	char		buffer[BUFFER_SIZE];

	if (fd < 0)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	append_buffer(prev, buffer, read_bytes);
	while (get_nl(buffer, read_bytes) < 0)
	{
		append_buffer(prev, buffer, read_bytes);
	}
}
