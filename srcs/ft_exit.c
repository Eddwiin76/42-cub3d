/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:45:58 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 18:07:47 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit(t_env *tab)
{
	int i;

	i = -1;
	close(tab->fd);
	ft_free_arg(&tab->arg);
	if (tab->validity.if_sprite != 0)
		free(tab->sprite);
	if (tab->buffer)
	{
		while (++i < tab->screen.y)
			free(tab->buffer[i]);
		free(tab->buffer);
	}
	ft_free_texture(tab);
	if (tab->img)
		ft_free_img(tab);
	ft_free_screen(&tab->screen);
	exit(0);
}
