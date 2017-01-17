/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:37:35 by jtranchi          #+#    #+#             */
/*   Updated: 2017/01/17 19:52:06 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void				ft_free(void *ptr)
{
	if (is_tiny(ptr))
		return ;
	else if (is_small(ptr))
		return ;
	else
		is_large(ptr);
	return ;
}

int 				main(void)
{
	char *str;
	int i;

	str = ft_malloc(42);
	i = -1;
	while (++i < 42)
		str[i] = 'a' + i % 26;
	return (0);
}