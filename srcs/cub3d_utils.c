/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 12:22:05 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/08 16:19:02 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_new_image(t_env *env, int width, int height)
{
	t_img *img;

	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	if (!(img->img_ptr = mlx_new_image(env->screen.mlx_ptr, width, height)))
		return (NULL);
	if (!(img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
		&img->sl, &img->endian)))
		return (NULL);
	img->width = width;
	img->height = height;
	return (img);
}

void	ft_draw(t_env *tab)
{
	int x;
	int y;

	y = 0;
	while (y < tab->screen.y)
	{
		x = 0;
		while (x < tab->screen.x)
		{
			tab->img->img_data[tab->screen.x * y + x] = tab->buffer[y][x];
			x++;
		}
		y++;
	}
}
