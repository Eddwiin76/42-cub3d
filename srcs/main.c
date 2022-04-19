/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 14:08:26 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 13:07:26 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_arg(int argc, char **argv)
{
	if (argc > 3)
		ft_error_arg(ERROR_TOO_MANY_ARG);
	if (argc < 2)
		ft_error_arg(ERROR_TOO_FEW_ARG);
	if (argc == 2)
		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
			ft_error_arg(ERROR_EXT_FILE);
	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 6) != 0)
			ft_error_arg(ERROR_SAVE_FLAG);
}

void	ft_initialyze2(t_env *tab)
{
	ft_bzero(&tab->screen, sizeof(t_screen));
	ft_bzero(&tab->img, sizeof(t_img));
	ft_bzero(&tab->texture_no, sizeof(t_img));
	ft_bzero(&tab->texture_so, sizeof(t_img));
	ft_bzero(&tab->texture_we, sizeof(t_img));
	ft_bzero(&tab->texture_ea, sizeof(t_img));
	ft_bzero(&tab->sprite_env, sizeof(t_img));
	ft_bzero(&tab->arg, sizeof(t_arg));
	ft_bzero(&tab->validity, sizeof(t_validity));
	ft_bzero(&tab->floor, sizeof(t_rgb));
	ft_bzero(&tab->ceil, sizeof(t_rgb));
	ft_bzero(&tab->player, sizeof(t_player));
	ft_bzero(&tab->player.pos, sizeof(t_pos));
	ft_bzero(&tab->move, sizeof(t_move));
	ft_bzero(&tab->ray, sizeof(t_ray));
	ft_bzero(tab, sizeof(t_env));
}

void	ft_initialyze(t_env *tab)
{
	tab->screen.mlx_ptr = NULL;
	tab->screen.win_ptr = NULL;
	tab->filename = NULL;
	tab->arg.screen = NULL;
	tab->arg.line_no = NULL;
	tab->arg.line_so = NULL;
	tab->arg.line_we = NULL;
	tab->arg.line_ea = NULL;
	tab->arg.line_s = NULL;
	tab->arg.floor = NULL;
	tab->arg.ceil = NULL;
	tab->arg.no = NULL;
	tab->arg.so = NULL;
	tab->arg.we = NULL;
	tab->arg.ea = NULL;
	tab->arg.s = NULL;
	tab->arg.map = NULL;
	tab->buffer = NULL;
	tab->z_buffer = NULL;
	ft_initialyze2(tab);
	tab->player.plane_y = 0.66;
}

int		main(int argc, char **argv)
{
	t_env	tab;

	ft_initialyze(&tab);
	ft_check_arg(argc, argv);
	if (argc == 3)
		tab.save = 1;
	tab.filename = argv[1];
	if (!(tab.screen.mlx_ptr = mlx_init()))
		ft_error(&tab, ERROR_MLX);
	ft_read(&tab);
	ft_init(&tab);
	if ((tab.img = ft_new_image(&tab, tab.screen.x, tab.screen.y)) == NULL)
		ft_error(&tab, ERROR_IMG);
	if (tab.save)
		ft_save(&tab);
	else
		ft_event(&tab);
	return (0);
}
