/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:43:39 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 17:45:30 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error3(int error)
{
	if (error == ERROR_SPRITE_DUPLICATE)
		ft_putstr_fd("Error\nDuplicate sprite path\n", 1);
	if (error == ERROR_NO_NO)
		ft_putstr_fd("Error\nNo NO texture\n", 1);
	if (error == ERROR_NO_SO)
		ft_putstr_fd("Error\nNo SO texture\n", 1);
	if (error == ERROR_NO_WE)
		ft_putstr_fd("Error\nNo WE texture\n", 1);
	if (error == ERROR_NO_EA)
		ft_putstr_fd("Error\nNo EA texture\n", 1);
	if (error == ERROR_NO_SPRITE)
		ft_putstr_fd("Error\nNo sprite texture\n", 1);
	if (error == ERROR_NO_FLOOR)
		ft_putstr_fd("Error\nNo floor detected\n", 1);
	if (error == ERROR_NO_CEIL)
		ft_putstr_fd("Error\nNo ceil detected\n", 1);
	if (error == ERROR_RESOLUTION_DUPLICATE)
		ft_putstr_fd("Error\nDuplicate resolution\n", 1);
	if (error == ERROR_FLOOR_DUPLICATE)
		ft_putstr_fd("Error\nDuplicate floor\n", 1);
	if (error == ERROR_CEIL_DUPLICATE)
		ft_putstr_fd("Error\nDuplicate ceil\n", 1);
	if (error == ERROR_NO_MAP)
		ft_putstr_fd("Error\nNo map detected\n", 1);
}

void	ft_error2(int error)
{
	if (error == ERROR_SPRITE_EXT)
		ft_putstr_fd("Error\nThe sprite must be a \".xpm\" file\n", 1);
	if (error == ERROR_IMG)
		ft_putstr_fd("Error\nError image\n", 1);
	if (error == ERROR_MLX)
		ft_putstr_fd("Error\nMLX failure\n", 1);
	if (error == ERROR_TOO_MANY_PLAYER)
		ft_putstr_fd("Error\nMultiplayer is comming soon, but not now !\n", 1);
	if (error == ERROR_NO_PLAYER)
		ft_putstr_fd("Error\nNo player detected\n", 1);
	if (error == ERROR_MAP)
		ft_putstr_fd("Error\nThis map is not valid\n", 1);
	if (error == ERROR_MAP_CHAR)
		ft_putstr_fd("Error\nThis map is not valid because of wrong char\n", 1);
	if (error == ERROR_MAP_NOT_CLOSE)
		ft_putstr_fd("Error\nIt is not a closed map\n", 1);
	if (error == ERROR_PLAYER_IS_AROUND)
		ft_putstr_fd("Error\nPlayer is around\n", 1);
	if (error == ERROR_MAP_NOT_LAST)
		ft_putstr_fd("Error\nThe map is not the last argument\n", 1);
	if (error == ERROR_UNKNOW_PARAM)
		ft_putstr_fd("Error\nThe parameter is unknown\n", 1);
	if (error == ERROR_NO_R)
		ft_putstr_fd("Error\nNo Resolution\n", 1);
}

void	ft_error(t_env *tab, int error)
{
	if (error == ERROR_INPUT)
		ft_putstr_fd("Error\nInvalid resolution or color input\n", 1);
	if (error == ERROR_RES)
		ft_putstr_fd("Error\nInvalid resolution input\n", 1);
	if (error == ERROR_COLOR)
		ft_putstr_fd("Error\nInvalid color input \n", 1);
	if (error == ERROR_MALLOC)
		ft_putstr_fd("Error\nMemory allocation failed\n", 1);
	if (error == ERROR_OPEN_FILE)
		ft_putstr_fd("Error\nImpossible to open the file\n", 1);
	if (error == ERROR_READ_FILE)
		ft_putstr_fd("Error\nImpossible to finish reading file\n", 1);
	if (error == ERROR_TEXTURE_PATH)
		ft_putstr_fd("Error\nWrong texture path\n", 1);
	if (error == ERROR_TEXTURE_DUPLICATE)
		ft_putstr_fd("Error\nDuplicate texture path\n", 1);
	if (error == ERROR_TEXTURE_EXT)
		ft_putstr_fd("Error\nThe texture must be a \".xpm\" file\n", 1);
	if (error == ERROR_TEXTURE_LOAD)
		ft_putstr_fd("Error\nLoad texture failed\n", 1);
	if (error == ERROR_SPRITE_PATH)
		ft_putstr_fd("Error\nWrong sprite path\n", 1);
	ft_error2(error);
	ft_error3(error);
	ft_exit(tab);
}

void	ft_error_arg(int error)
{
	if (error == ERROR_TOO_MANY_ARG)
		ft_putstr_fd("Error\nToo many arguments\n", 1);
	if (error == ERROR_TOO_FEW_ARG)
		ft_putstr_fd("Error\nNot enough arguments\n", 1);
	if (error == ERROR_EXT_FILE)
		ft_putstr_fd("Error\nThe first argument it's not a \".cub\" file\n", 1);
	if (error == ERROR_SAVE_FLAG)
		ft_putstr_fd("Error\nNot a valid flag\n", 1);
	exit(0);
}
