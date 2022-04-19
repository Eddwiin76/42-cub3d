/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:11:58 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/07 12:51:54 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_ray(t_env *tab, int x)
{
	double camera_x;

	camera_x = 2 * x / (double)tab->screen.x - 1;
	tab->ray.ray_dir_x = tab->player.dir_x + tab->player.plane_x * camera_x;
	tab->ray.ray_dir_y = tab->player.dir_y + tab->player.plane_y * camera_x;
	tab->ray.map_x = (int)tab->player.pos.x;
	tab->ray.map_y = (int)tab->player.pos.y;
	tab->ray.delta_dist_x = fabs(1 / tab->ray.ray_dir_x);
	tab->ray.delta_dist_y = fabs(1 / tab->ray.ray_dir_y);
	tab->ray.hit = 0;
	tab->ray.step_x = (tab->ray.ray_dir_x < 0) ? -1 : 1;
	tab->ray.side_dist_x = (tab->ray.ray_dir_x < 0) ?
		(tab->player.pos.x - tab->ray.map_x) * tab->ray.delta_dist_x
		: (tab->ray.map_x + 1.0 - tab->player.pos.x) * tab->ray.delta_dist_x;
	tab->ray.step_y = (tab->ray.ray_dir_y < 0) ? -1 : 1;
	tab->ray.side_dist_y = (tab->ray.ray_dir_y < 0) ?
		(tab->player.pos.y - tab->ray.map_y) * tab->ray.delta_dist_y
		: (tab->ray.map_y + 1.0 - tab->player.pos.y) * tab->ray.delta_dist_y;
	tab->ray.x = x;
}

void	ft_perform_dist(t_env *tab)
{
	while (tab->ray.hit == 0)
	{
		if (tab->ray.side_dist_x < tab->ray.side_dist_y)
		{
			tab->ray.side_dist_x += tab->ray.delta_dist_x;
			tab->ray.map_x += tab->ray.step_x;
			tab->ray.side = 0;
		}
		else
		{
			tab->ray.side_dist_y += tab->ray.delta_dist_y;
			tab->ray.map_y += tab->ray.step_y;
			tab->ray.side = 1;
		}
		if (tab->arg.map[tab->ray.map_y][tab->ray.map_x] == '1')
			tab->ray.hit = 1;
	}
	if (tab->ray.side == 0)
		tab->ray.perp_wall_dist = (tab->ray.map_x - tab->player.pos.x
				+ (1 - tab->ray.step_x) / 2) / tab->ray.ray_dir_x;
	else
		tab->ray.perp_wall_dist = (tab->ray.map_y - tab->player.pos.y
			+ (1 - tab->ray.step_y) / 2) / tab->ray.ray_dir_y;
}

void	ft_display_texture2(t_env *tab, t_texture *tex)
{
	tex->wall_x -= floor(tex->wall_x);
	tex->tex_x = (int)(tex->wall_x * (double)(tex->texture_img->width));
	if (tab->ray.side == 0 && tab->ray.ray_dir_x > 0)
		tex->tex_x = tex->texture_img->width - tex->tex_x - 1;
	if (tab->ray.side == 1 && tab->ray.ray_dir_y < 0)
		tex->tex_x = tex->texture_img->width - tex->tex_x - 1;
	tex->step = 1.0 * tex->texture_img->height / tab->ray.line_height;
	tex->tex_pos = (tab->ray.draw_start - tab->screen.y / 2
			+ tab->ray.line_height / 2) * tex->step;
	tex->y = tab->ray.draw_start - 1;
	while (++tex->y < tab->ray.draw_end)
	{
		tex->tex_y = (int)tex->tex_pos & (tex->texture_img->height - 1);
		tex->tex_pos += tex->step;
		tex->color = tex->texture_img->img_data[tex->texture_img->width
				* tex->tex_y + tex->tex_x];
		if (tab->ray.side == 1)
			tex->color = (tex->color >> 1) & 8355711;
		tab->buffer[tex->y][tab->ray.x] = tex->color;
	}
}

void	ft_display_texture(t_env *tab)
{
	t_texture	tex;

	if (tab->ray.side == 1 && tab->ray.ray_dir_y > 0)
		tex.texture_img = &tab->texture_so;
	if (tab->ray.side == 1 && tab->ray.ray_dir_y < 0)
		tex.texture_img = &tab->texture_no;
	if (tab->ray.side == 0 && tab->ray.ray_dir_x > 0)
		tex.texture_img = &tab->texture_ea;
	if (tab->ray.side == 0 && tab->ray.ray_dir_x < 0)
		tex.texture_img = &tab->texture_we;
	if (tab->ray.side == 0)
		tex.wall_x = tab->player.pos.y + tab->ray.perp_wall_dist
				* tab->ray.ray_dir_y;
	else
		tex.wall_x = tab->player.pos.x + tab->ray.perp_wall_dist
				* tab->ray.ray_dir_x;
	ft_display_texture2(tab, &tex);
}

void	ft_display_wall(t_env *tab)
{
	int x;

	x = -1;
	while (++x < tab->screen.x)
	{
		ft_init_ray(tab, x);
		ft_perform_dist(tab);
		tab->ray.line_height = (int)(tab->screen.y / tab->ray.perp_wall_dist);
		tab->ray.draw_start = -tab->ray.line_height / 2 + tab->screen.y / 2;
		if (tab->ray.draw_start < 0)
			tab->ray.draw_start = 0;
		tab->ray.draw_end = tab->ray.line_height / 2 + tab->screen.y / 2;
		if (tab->ray.draw_end >= tab->screen.y)
			tab->ray.draw_end = tab->screen.y - 1;
		ft_display_texture(tab);
		tab->z_buffer[x] = tab->ray.perp_wall_dist;
	}
}
