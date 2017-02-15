/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:37:35 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/15 17:50:38 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void				*malloc(size_t size)
{
	static int		flag = 0;

	if (size <= 0)
		return (NULL);
	if (flag == 0)
	{
		g_m.tiny = NULL;
		g_m.small = NULL;
		g_m.large = NULL;
		flag = 1;
	}
	if (size <= (size_t)TINY)
		return (tiny_malloc(size));
	else if (size <= (size_t)PAGE)
		return (small_malloc(size));
	else
		return (large_malloc(size));
}
