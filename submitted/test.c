/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:15:16 by dlu               #+#    #+#             */
/*   Updated: 2023/05/08 19:08:57 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
/*
void	test2(int d, int **p)
{
	if (!*p)
	{
		printf("mallocing");
		*p = (int *) malloc(sizeof(int));
	}
	**p = d;
}
*/
void	test3(char *s, char *p)
{
	*p = d;
}
/*
int	test(int d)
{
	static int	*p;
	//if (!i)
	//	i = NULL;
	//test2(d, p);
	return (*p);
}*/

int	main(void)
{
	static char	*p;

	//if (!p)
	//	p =
	//test2(1, &p);
	//printf("%d\n", *p);
	//test2(2, &p);
	//printf("%d\n", *p);
	//free(p);
	test3(2, p);
	printf("%d\n", *p);
	return (0);
}
