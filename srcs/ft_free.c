/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:55:38 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 18:01:17 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_texture(t_env *tab)
{
	if (tab->texture_no.img_ptr)
		mlx_destroy_image(tab->screen.mlx_ptr, tab->texture_no.img_ptr);
	if (tab->texture_so.img_ptr)
		mlx_destroy_image(tab->screen.mlx_ptr, tab->texture_so.img_ptr);
	if (tab->texture_we.img_ptr)
		mlx_destroy_image(tab->screen.mlx_ptr, tab->texture_we.img_ptr);
	if (tab->texture_ea.img_ptr)
		mlx_destroy_image(tab->screen.mlx_ptr, tab->texture_ea.img_ptr);
	if (tab->sprite_env.img_ptr)
		mlx_destroy_image(tab->screen.mlx_ptr, tab->sprite_env.img_ptr);
}

void	ft_free_arg(t_arg *arg)
{
	free(arg->screen);
	free(arg->line_no);
	free(arg->line_so);
	free(arg->line_we);
	free(arg->line_ea);
	free(arg->line_s);
	free(arg->floor);
	free(arg->ceil);
	free(arg->no);
	free(arg->so);
	free(arg->we);
	free(arg->ea);
	free(arg->s);
	ft_tabdel((void **)arg->map);
}

void	ft_free_screen(t_screen *screen)
{
	if (screen->windowcreated == 1)
		mlx_destroy_window(screen->mlx_ptr, screen->win_ptr);
	if (screen->mlx_ptr)
		free(screen->mlx_ptr);
}

void	ft_free_img(t_env *tab)
{
	mlx_destroy_image(tab->screen.mlx_ptr, tab->img->img_ptr);
	free(tab->img);
	tab->img = NULL;
}
