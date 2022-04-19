/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 10:52:42 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 16:51:16 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_validity(t_env *tab)
{
	if (tab->validity.if_resolution == 0)
		ft_error(tab, ERROR_NO_R);
	if (tab->validity.if_texture_no == 0)
		ft_error(tab, ERROR_NO_NO);
	if (tab->validity.if_texture_so == 0)
		ft_error(tab, ERROR_NO_SO);
	if (tab->validity.if_texture_we == 0)
		ft_error(tab, ERROR_NO_WE);
	if (tab->validity.if_texture_ea == 0)
		ft_error(tab, ERROR_NO_EA);
	if (tab->validity.if_sprite != 0 && tab->validity.if_texture_sprite == 0)
		ft_error(tab, ERROR_NO_SPRITE);
	if (tab->validity.if_colors_floor == 0)
		ft_error(tab, ERROR_NO_FLOOR);
	if (tab->validity.if_colors_ceil == 0)
		ft_error(tab, ERROR_NO_CEIL);
	if (tab->validity.if_map == 0)
		ft_error(tab, ERROR_NO_MAP);
}

void	ft_init_sprite(t_env *tab)
{
	if (!(tab->sprite_env.img_ptr = mlx_xpm_file_to_image(tab->screen.mlx_ptr,
			tab->arg.s, &tab->sprite_env.width, &tab->sprite_env.height)))
		ft_error(tab, ERROR_TEXTURE_LOAD);
	tab->sprite_env.img_data = (int *)mlx_get_data_addr(tab->sprite_env.img_ptr,
			&tab->sprite_env.bpp, &tab->sprite_env.sl, &tab->sprite_env.endian);
}

void	ft_init_texture(t_env *tab)
{
	if (!(tab->texture_no.img_ptr = mlx_xpm_file_to_image(tab->screen.mlx_ptr,
			tab->arg.no, &tab->texture_no.width, &tab->texture_no.height)))
		ft_error(tab, ERROR_TEXTURE_LOAD);
	tab->texture_no.img_data = (int *)mlx_get_data_addr(tab->texture_no.img_ptr,
			&tab->texture_no.bpp, &tab->texture_no.sl, &tab->texture_no.endian);
	if (!(tab->texture_so.img_ptr = mlx_xpm_file_to_image(tab->screen.mlx_ptr,
			tab->arg.so, &tab->texture_so.width, &tab->texture_so.height)))
		ft_error(tab, ERROR_TEXTURE_LOAD);
	tab->texture_so.img_data = (int *)mlx_get_data_addr(tab->texture_so.img_ptr,
			&tab->texture_so.bpp, &tab->texture_so.sl, &tab->texture_so.endian);
	if (!(tab->texture_we.img_ptr = mlx_xpm_file_to_image(tab->screen.mlx_ptr,
			tab->arg.we, &tab->texture_we.width, &tab->texture_we.height)))
		ft_error(tab, ERROR_TEXTURE_LOAD);
	tab->texture_we.img_data = (int *)mlx_get_data_addr(tab->texture_we.img_ptr,
			&tab->texture_we.bpp, &tab->texture_we.sl, &tab->texture_we.endian);
	if (!(tab->texture_ea.img_ptr = mlx_xpm_file_to_image(tab->screen.mlx_ptr,
			tab->arg.ea, &tab->texture_ea.width, &tab->texture_ea.height)))
		ft_error(tab, ERROR_TEXTURE_LOAD);
	tab->texture_ea.img_data = (int *)mlx_get_data_addr(tab->texture_ea.img_ptr,
			&tab->texture_ea.bpp, &tab->texture_ea.sl, &tab->texture_ea.endian);
	if (tab->validity.if_sprite != 0)
		ft_init_sprite(tab);
}

void	ft_init2(t_env *tab)
{
	ft_check_validity(tab);
	ft_get_screen(tab, &tab->screen, tab->arg.screen);
	ft_get_color(tab, &tab->floor, tab->arg.floor);
	ft_get_color(tab, &tab->ceil, tab->arg.ceil);
	ft_check_path2(tab, &tab->arg.no, tab->arg.line_no);
	ft_check_path2(tab, &tab->arg.so, tab->arg.line_so);
	ft_check_path2(tab, &tab->arg.we, tab->arg.line_we);
	ft_check_path2(tab, &tab->arg.ea, tab->arg.line_ea);
	ft_check_path_s(tab, &tab->arg.s, tab->arg.line_s);
	ft_check_player(tab, tab->arg.map, &tab->player);
	ft_check_player2(tab);
	ft_check_map_char(tab, tab->arg.map, 0);
	ft_check_map_around(tab, tab->arg.map);
}

void	ft_init(t_env *tab)
{
	int i;

	ft_init2(tab);
	if (!(tab->buffer = ft_calloc(tab->screen.y, sizeof(int **))))
		ft_error(tab, ERROR_MALLOC);
	i = -1;
	while (++i < tab->screen.y)
		if (!(tab->buffer[i] = ft_calloc(tab->screen.x, sizeof(int *))))
			ft_error(tab, ERROR_MALLOC);
	ft_init_texture(tab);
	if (tab->validity.if_sprite != 0)
	{
		if (!(tab->sprite = (t_sprite *)malloc(sizeof(t_sprite)
				* tab->validity.if_sprite)))
			ft_error(tab, ERROR_MALLOC);
		i = -1;
		while (++i < tab->validity.if_sprite)
			ft_bzero(&tab->sprite[i], sizeof(t_sprite));
		ft_check_map_char(tab, tab->arg.map, 1);
	}
}
