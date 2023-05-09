/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:34:36 by dlu               #+#    #+#             */
/*   Updated: 2023/05/09 22:47:05 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Get the length of the string. */
static int	ft_strlen(char *s)
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
	int		i;

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

/* Return the index of '\n', or the index of the '\0' if at the end. */
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

int	append_buffer(char **prev, char *buffer, ssize_t n)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	if (n < 0)
		return (0);
	len = ft_strlen(*prev);
	tmp = (char *) malloc((len + n + 1) * sizeof(char));
	if (!tmp)
		return (0);
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
	return (1);
}
