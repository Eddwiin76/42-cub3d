/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:14:51 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/08 12:02:38 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sort_sprites(t_env *tab)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++i < tab->validity.if_sprite)
	{
		j = -1;
		while (++j < tab->validity.if_sprite - 1)
		{
			if (tab->sprite[j].distance < tab->sprite[j + 1].distance)
			{
				tmp = tab->sprite[j];
				tab->sprite[j] = tab->sprite[j + 1];
				tab->sprite[j + 1] = tmp;
			}
		}
	}
}

void	ft_sprite_position(t_env *tab, t_ray_sprite *sprite, int i)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = tab->sprite[i].x - tab->player.pos.x;
	sprite_y = tab->sprite[i].y - tab->player.pos.y;
	inv_det = 1.0 / (tab->player.plane_x * tab->player.dir_y - tab->player.dir_x
			* tab->player.plane_y);
	sprite->transform_x = inv_det * (tab->player.dir_y
			* sprite_x - tab->player.dir_x * sprite_y);
	sprite->transform_y = inv_det * (-tab->player.plane_y
			* sprite_x + tab->player.plane_x * sprite_y);
	sprite->sp_screen_x = (int)((tab->screen.x / 2)
			* (1 + sprite->transform_x / sprite->transform_y));
}

void	ft_sprite_size(t_env *tab, t_ray_sprite *sprite)
{
	sprite->sp_height = abs((int)(tab->screen.y / sprite->transform_y));
	sprite->draw_start_y = -sprite->sp_height / 2 + tab->screen.y / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->sp_height / 2 + tab->screen.y / 2;
	if (sprite->draw_end_y >= tab->screen.y)
		sprite->draw_end_y = tab->screen.y - 1;
	sprite->sp_width = abs((int)(tab->screen.y / sprite->transform_y));
	sprite->draw_start_x = -sprite->sp_width / 2 + sprite->sp_screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->sp_width / 2 + sprite->sp_screen_x;
	if (sprite->draw_end_x >= tab->screen.x)
		sprite->draw_end_x = tab->screen.x - 1;
}

void	ft_display_each_sprite(t_env *tab, t_ray_sprite *sp)
{
	int		stripe;
	int		y;
	int		d;
	int		color;

	stripe = sp->draw_start_x - 1;
	while (++stripe < sp->draw_end_x)
	{
		sp->tex_x = (int)(256 * (stripe - (-sp->sp_width / 2 +
				sp->sp_screen_x)) * sp->sp_img->width / sp->sp_width) / 256;
		if (sp->transform_y > 0 && stripe > 0 && stripe < tab->screen.x
				&& sp->transform_y < tab->z_buffer[stripe])
		{
			y = sp->draw_start_y - 1;
			while (++y < sp->draw_end_y)
			{
				d = y * 256 - tab->screen.y * 128 + sp->sp_height * 128;
				sp->tex_y = ((d * sp->sp_img->height) / sp->sp_height) / 256;
				color = sp->sp_img->img_data[sp->sp_img->width
					* sp->tex_y + sp->tex_x];
				if ((color & 0x00FFFFFF) != 0 && color != PINK)
					tab->buffer[y][stripe] = color;
			}
		}
	}
}

void	ft_display_sprite(t_env *tab)
{
	t_ray_sprite	sprite;
	int				i;

	i = -1;
	while (++i < tab->validity.if_sprite)
	{
		tab->sprite[i].distance = ((tab->player.pos.x - tab->sprite[i].x) *
				(tab->player.pos.x - tab->sprite[i].x) +
				(tab->player.pos.y - tab->sprite[i].y) *
				(tab->player.pos.y - tab->sprite[i].y));
	}
	ft_sort_sprites(tab);
	i = -1;
	while (++i < tab->validity.if_sprite)
	{
		sprite.sp_img = &tab->sprite_env;
		ft_sprite_position(tab, &sprite, i);
		ft_sprite_size(tab, &sprite);
		ft_display_each_sprite(tab, &sprite);
	}
}
