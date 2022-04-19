/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:13:17 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/09 12:24:06 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	g_header[54] = {66, 77, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0, 40,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 32};
int		*g_size = (int *)&g_header[2];
int		*g_x = (int *)&g_header[18];
int		*g_y = (int *)&g_header[22];

void	ft_save(t_env *tab)
{
	int fd;

	ft_run(tab);
	if (!(fd = open("save.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)))
		ft_error(tab, ERROR_OPEN_FILE);
	*g_size = 4 * (tab->screen.x * tab->screen.y) + 54;
	*g_x = tab->screen.x;
	*g_y -= tab->screen.y;
	write(fd, g_header, 54);
	write(fd, tab->img->img_data, ((size_t)*g_size) - 54);
	close(fd);
	ft_error(tab, SUCCESS);
}
