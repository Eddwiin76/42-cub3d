/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:09:04 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 18:14:24 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_rgb_to_hex(int r, int g, int b)
{
	unsigned int	output;

	output = 256 * 256 * r + 256 * g + b;
	return (output);
}

int				ft_color(char *str)
{
	int	i;
	int	color;

	i = -1;
	if (ft_strlen(str) == 0)
		return (ERROR_COLOR);
	while (str[++i])
		if (!ft_isdigit(str[i]))
		{
			free(str);
			return (ERROR_COLOR);
		}
	color = ft_atoi(str);
	if (color > 255 || color < 0)
	{
		free(str);
		return (ERROR_COLOR);
	}
	free(str);
	return (SUCCESS);
}

void			ft_get_color(t_env *tab, t_rgb *rgb, char *line)
{
	char	**tmptab;

	if (ft_strcountchar(line, ',') != 2)
		ft_error(tab, ERROR_COLOR);
	if (!(tmptab = ft_split(line, ',')))
		ft_error(tab, ERROR_MALLOC);
	if (ft_tabsize(tmptab) == 3)
	{
		if (((tab->error = ft_color(ft_strtrim(tmptab[0], " "))) != SUCCESS)
			|| ((tab->error = ft_color(ft_strtrim(tmptab[1], " "))) != SUCCESS)
			|| ((tab->error = ft_color(ft_strtrim(tmptab[2], " "))) != SUCCESS))
		{
			ft_tabdel((void **)tmptab);
			ft_error(tab, tab->error);
		}
	}
	else
	{
		ft_tabdel((void **)tmptab);
		ft_error(tab, ERROR_COLOR);
	}
	rgb->rgb = ft_rgb_to_hex(ft_atoi(tmptab[0]), ft_atoi(tmptab[1]),
			ft_atoi(tmptab[2]));
	ft_tabdel((void **)tmptab);
}

int				ft_check_screen(t_screen *screen)
{
	int	x;
	int	y;

	mlx_get_screen_size(screen->mlx_ptr, &x, &y);
	if (screen->x > x)
		screen->x = x;
	if (screen->y > y)
		screen->y = y;
	if (screen->x <= 0)
		return (ERROR_RES);
	if (screen->y <= 0)
		return (ERROR_RES);
	return (SUCCESS);
}

void			ft_get_screen(t_env *tab, t_screen *screen, char *line)
{
	char	**tmptab;

	if (!(tmptab = ft_split(line, ' ')))
		ft_error(tab, ERROR_MALLOC);
	if (ft_tabsize(tmptab) == 2 && ft_isalldigit(tmptab[0])
			&& ft_isalldigit(tmptab[1]))
	{
		screen->x = ft_atoi(tmptab[0]);
		screen->y = ft_atoi(tmptab[1]);
		if ((tab->error = ft_check_screen(screen)) != SUCCESS)
		{
			ft_tabdel((void **)tmptab);
			ft_error(tab, tab->error);
		}
	}
	else
	{
		ft_tabdel((void **)tmptab);
		ft_error(tab, ERROR_RES);
	}
	ft_tabdel((void **)tmptab);
}
