/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:37:35 by jtranchi          #+#    #+#             */
/*   Updated: 2017/01/18 14:20:02 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void				*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1c;
	unsigned char	*s2c;

	i = 0;
	s1c = (unsigned char *)s1;
	s2c = (unsigned char *)s2;
	while (i < n)
	{
		s1c[i] = s2c[i];
		i++;
	}
	return (s1);
}

void				free(void *ptr)
{
	if (is_tiny(ptr))
		return ;
	else if (is_small(ptr))
		return ;
	else
		is_large(ptr);
	return ;
}
