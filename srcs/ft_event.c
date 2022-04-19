/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:07:20 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/12 11:39:04 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move(t_env *tab)
{
	if (tab->move.up == 1 || tab->move.down == 1)
		ft_move_up_down(tab);
	if (tab->move.left == 1 || tab->move.right == 1)
		ft_move_left_rigth(tab);
	if (tab->move.strafr == 1)
		ft_rotate(tab, SPEED);
	if (tab->move.strafl == 1)
		ft_rotate(tab, -1 * SPEED);
}

int		ft_key_press(int key, t_env *tab)
{
	if (key == KEY_ESCAPE)
		ft_error(tab, tab->error);
	if (key == KEY_Z || key == KEY_W)
		tab->move.up = 1;
	if (key == KEY_S)
		tab->move.down = 1;
	if (key == KEY_Q || key == KEY_A)
		tab->move.left = 1;
	if (key == KEY_D)
		tab->move.right = 1;
	if (key == KEY_RIGHT)
		tab->move.strafr = 1;
	if (key == KEY_LEFT)
		tab->move.strafl = 1;
	return (0);
}

int		ft_key_release(int key, t_env *tab)
{
	if (key == KEY_Z || key == KEY_W)
		tab->move.up = 0;
	if (key == KEY_S)
		tab->move.down = 0;
	if (key == KEY_Q || key == KEY_A)
		tab->move.left = 0;
	if (key == KEY_D)
		tab->move.right = 0;
	if (key == KEY_RIGHT)
		tab->move.strafr = 0;
	if (key == KEY_LEFT)
		tab->move.strafl = 0;
	return (0);
}

int		ft_run(t_env *tab)
{
	if (tab->img)
		ft_free_img(tab);
	if ((tab->img = ft_new_image(tab, tab->screen.x, tab->screen.y)) == NULL)
		ft_error(tab, ERROR_IMG);
	ft_move(tab);
	ft_display(tab);
	if (!tab->save)
		mlx_put_image_to_window(tab->screen.mlx_ptr, tab->screen.win_ptr,
			tab->img->img_ptr, 0, 0);
	return (SUCCESS);
}

void	ft_event(t_env *tab)
{
	if (!(tab->screen.win_ptr = mlx_new_window(tab->screen.mlx_ptr,
			tab->screen.x, tab->screen.y, "Cub3D")))
		ft_error(tab, ERROR_MLX);
	tab->screen.windowcreated = 1;
	mlx_hook(tab->screen.win_ptr, 2, 1L << 0, ft_key_press, tab);
	mlx_hook(tab->screen.win_ptr, 3, 1L << 1, ft_key_release, tab);
	mlx_hook(tab->screen.win_ptr, 17, 1L << 17, ft_exit, tab);
	mlx_loop_hook(tab->screen.mlx_ptr, ft_run, tab);
	mlx_loop(tab->screen.mlx_ptr);
}
