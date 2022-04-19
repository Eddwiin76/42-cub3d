/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 14:59:57 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/08 16:13:20 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_display_floor_ceil(t_env *tab)
{
	int x;
	int y;

	x = -1;
	y = -1;
	while (++y < tab->screen.y)
	{
		x = 0;
		while (++x < tab->screen.x)
		{
			if (y < tab->screen.y / 2)
				tab->buffer[y][x] = tab->ceil.rgb;
			else if (y >= tab->screen.y / 2)
				tab->buffer[y][x] = tab->floor.rgb;
		}
	}
}

void	ft_display(t_env *tab)
{
	if (!(tab->z_buffer = ft_calloc(tab->screen.x, sizeof(double *))))
		ft_error(tab, ERROR_MALLOC);
	ft_display_floor_ceil(tab);
	ft_display_wall(tab);
	if (tab->validity.if_sprite != 0)
		ft_display_sprite(tab);
	ft_draw(tab);
	free(tab->z_buffer);
}
