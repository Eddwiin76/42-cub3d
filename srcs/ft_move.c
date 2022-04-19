/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:25:08 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/08 16:59:51 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_left_rigth(t_env *tab)
{
	char	pos1;
	char	pos2;

	if (tab->move.left == 1)
	{
		pos1 = tab->arg.map[(int)tab->player.pos.y][(int)(tab->player.pos.x
				+ tab->player.dir_y * SPEED)];
		pos2 = tab->arg.map[(int)(tab->player.pos.y - tab->player.dir_x
				* SPEED)][(int)tab->player.pos.x];
		if (pos1 != '1' && pos1 != '2')
			tab->player.pos.x += tab->player.dir_y * SPEED;
		if (pos2 != '1' && pos2 != '2')
			tab->player.pos.y -= tab->player.dir_x * SPEED;
	}
	if (tab->move.right == 1)
	{
		pos1 = tab->arg.map[(int)tab->player.pos.y][(int)(tab->player.pos.x
				- tab->player.dir_y * SPEED)];
		pos2 = tab->arg.map[(int)(tab->player.pos.y + tab->player.dir_x
				* SPEED)][(int)tab->player.pos.x];
		if (pos1 != '1' && pos1 != '2')
			tab->player.pos.x -= tab->player.dir_y * SPEED;
		if (pos2 != '1' && pos2 != '2')
			tab->player.pos.y += tab->player.dir_x * SPEED;
	}
}

void	ft_move_up_down(t_env *tab)
{
	char	pos1;
	char	pos2;

	if (tab->move.up == 1)
	{
		pos1 = tab->arg.map[(int)tab->player.pos.y][(int)(tab->player.pos.x
				+ tab->player.dir_x * SPEED)];
		pos2 = tab->arg.map[(int)(tab->player.pos.y + tab->player.dir_y
				* SPEED)][(int)tab->player.pos.x];
		if (pos1 != '1' && pos1 != '2')
			tab->player.pos.x += tab->player.dir_x * SPEED;
		if (pos2 != '1' && pos2 != '2')
			tab->player.pos.y += tab->player.dir_y * SPEED;
	}
	if (tab->move.down == 1)
	{
		pos1 = tab->arg.map[(int)tab->player.pos.y][(int)(tab->player.pos.x
				- tab->player.dir_x * SPEED)];
		pos2 = tab->arg.map[(int)(tab->player.pos.y - tab->player.dir_y
				* SPEED)][(int)tab->player.pos.x];
		if (pos1 != '1' && pos1 != '2')
			tab->player.pos.x -= tab->player.dir_x * SPEED;
		if (pos2 != '1' && pos2 != '2')
			tab->player.pos.y -= tab->player.dir_y * SPEED;
	}
}

void	ft_rotate(t_env *tab, double degree)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = tab->player.dir_x;
	tab->player.dir_x = tab->player.dir_x * cos(degree) - tab->player.dir_y
		* sin(degree);
	tab->player.dir_y = old_dir_x * sin(degree) + tab->player.dir_y
		* cos(degree);
	old_plane_x = tab->player.plane_x;
	tab->player.plane_x =
		tab->player.plane_x * cos(degree) - tab->player.plane_y
			* sin(degree);
	tab->player.plane_y =
		old_plane_x * sin(degree) + tab->player.plane_y * cos(degree);
}
