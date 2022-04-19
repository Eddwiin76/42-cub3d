/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:00:00 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 17:12:56 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_map_is_0(t_env *tab, int i, int j, char **map)
{
	if (i == 0 || j == 0 || i == tab->arg.mapx - 1
		|| j == (int)ft_strlen(map[i]) - 1
		|| j >= (int)ft_strlen(map[i - 1])
		|| j >= (int)ft_strlen(map[i + 1]))
		ft_error(tab, ERROR_MAP_NOT_CLOSE);
}

void	ft_check_map_is_blank(t_env *tab, int i, int j, char **map)
{
	if (i != 0 && (map[i - 1][j] == '0'
			|| map[i - 1][j] == tab->player.orientation
			|| map[i - 1][j] == '2'))
		ft_error(tab, ERROR_MAP_NOT_CLOSE);
	if (i != tab->arg.mapx - 1 && (map[i + 1][j] == '0'
			|| map[i + 1][j] == tab->player.orientation
			|| map[i + 1][j] == '2'))
		ft_error(tab, ERROR_MAP_NOT_CLOSE);
	if (j != 0 && (map[i][j - 1] == '0'
			|| map[i][j - 1] == tab->player.orientation
			|| map[i][j - 1] == '2'))
		ft_error(tab, ERROR_MAP_NOT_CLOSE);
	if (j != tab->arg.mapy && (map[i][j + 1] == '0'
			|| map[i][j + 1] == tab->player.orientation
			|| map[i][j + 1] == '2'))
		ft_error(tab, ERROR_MAP_NOT_CLOSE);
}

void	ft_check_map_around(t_env *tab, char **map)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
				ft_check_map_is_0(tab, i, j, map);
			if (map[i][j] == ' ')
				ft_check_map_is_blank(tab, i, j, map);
			if (map[i][j] == '2')
				tab->validity.if_sprite += 1;
		}
	}
}

void	ft_check_map_char(t_env *tab, char **map, int if_two)
{
	int i;
	int j;
	int x;

	x = -1;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (if_two == 0)
			{
				if (!(ft_strchr(" 012NSEW", map[i][j])))
					ft_error(tab, ERROR_MAP_CHAR);
			}
			else if (if_two == 1)
				if (map[i][j] == '2')
				{
					tab->sprite[++x].x = j + 0.5;
					tab->sprite[x].y = i + 0.5;
				}
		}
	}
}

int		ft_get_map(t_env *tab, char *line)
{
	static int i;

	if (i == 0)
	{
		if (!(tab->arg.map = (char **)malloc(sizeof(char *) * (1 + 1))))
			return (ERROR_MALLOC);
	}
	else
	{
		if (!(tab->arg.map = (char **)ft_realloc(tab->arg.map,
				sizeof(char *) * i, sizeof(char *) * (i + 2))))
			return (ERROR_MALLOC);
	}
	if (!(tab->arg.map[i] = ft_strdup(line)))
		return (ERROR_MALLOC);
	i++;
	tab->arg.map[i] = NULL;
	return (SUCCESS);
}
