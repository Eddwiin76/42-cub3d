/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:36:16 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 17:46:24 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_player2(t_env *tab)
{
	if (tab->player.orientation == 'N')
	{
		tab->player.dir_x = 0.0;
		tab->player.dir_y = -1.0;
	}
	if (tab->player.orientation == 'E')
	{
		tab->player.dir_x = 1.0;
		tab->player.dir_y = 0.0;
	}
	if (tab->player.orientation == 'S')
	{
		tab->player.dir_x = 0.0;
		tab->player.dir_y = 1.0;
	}
	if (tab->player.orientation == 'W')
	{
		tab->player.dir_x = -1.0;
		tab->player.dir_y = 0.0;
	}
	tab->player.plane_x = tab->player.dir_y * -0.66;
	tab->player.plane_y = tab->player.dir_x * 0.66;
}

void	ft_check_player(t_env *tab, char **map, t_player *player)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (ft_strchr("NSWE", map[i][j]))
			{
				if (player->orientation != 0)
					ft_error(tab, ERROR_TOO_MANY_PLAYER);
				else
				{
					player->orientation = map[i][j];
					player->pos.x = (double)j + 0.5;
					player->pos.y = (double)i + 0.5;
				}
			}
		if (tab->arg.mapy < j)
			tab->arg.mapy = j;
	}
	tab->arg.mapx = i;
	if (!player->orientation)
		ft_error(tab, ERROR_NO_PLAYER);
}
