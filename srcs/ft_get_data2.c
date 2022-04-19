/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:50:47 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 14:22:00 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_path_ext(t_env *tab, char **orientation, int o)
{
	(void)tab;
	if (o == 0)
		if (ft_strncmp(*orientation + ft_strlen(*orientation) - 4,
				".xpm", 4) != 0)
			ft_error(tab, ERROR_SPRITE_EXT);
	if (o == 1)
		if ((ft_strncmp(*orientation + ft_strlen(*orientation) - 4,
				".xpm", 4) != 0)
			|| (ft_strncmp(*orientation + ft_strlen(*orientation) - 4,
					".xpm", 4) != 0))
			ft_error(tab, ERROR_TEXTURE_EXT);
}

void	ft_check_path_s(t_env *tab, char **orientation, char *line)
{
	int fd;

	if (!(*orientation = ft_strtrim(line + 1, " ")))
		ft_error(tab, ERROR_MALLOC);
	ft_check_path_ext(tab, orientation, 0);
	fd = open(*orientation, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_error(tab, ERROR_SPRITE_PATH);
	}
	close(fd);
}

void	ft_check_path2(t_env *tab, char **orientation, char *line)
{
	int fd;

	if (!(*orientation = ft_strtrim(line, " ")))
		ft_error(tab, ERROR_MALLOC);
	ft_check_path_ext(tab, orientation, 1);
	fd = open(*orientation, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_error(tab, ERROR_TEXTURE_PATH);
	}
	close(fd);
}

int		ft_parse_path2(t_env *tab, char *line, int *i)
{
	if (line[*i] == 'W' && line[*i + 1] == 'E' && line[*i + 2] == ' ')
	{
		if (tab->validity.if_texture_we == 1)
			return (ERROR_TEXTURE_DUPLICATE);
		tab->arg.line_we = ft_strdup(line + (*i + 2));
		tab->validity.if_texture_we = 1;
	}
	else if (line[*i] == 'E' && line[*i + 1] == 'A' && line[*i + 2] == ' ')
	{
		if (tab->validity.if_texture_ea == 1)
			return (ERROR_TEXTURE_DUPLICATE);
		tab->arg.line_ea = ft_strdup(line + (*i + 2));
		tab->validity.if_texture_ea = 1;
	}
	else if (ft_strlen(line) != 0)
		return (ERROR_UNKNOW_PARAM);
	return (SUCCESS);
}

int		ft_parse_path(t_env *tab, char *line, int *i)
{
	if (line[*i] == 'N' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
	{
		if (tab->validity.if_texture_no == 1)
			return (ERROR_TEXTURE_DUPLICATE);
		tab->arg.line_no = ft_strdup(line + (*i + 2));
		tab->validity.if_texture_no = 1;
	}
	else if (line[*i] == 'S' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
	{
		if (tab->validity.if_texture_so == 1)
			return (ERROR_TEXTURE_DUPLICATE);
		tab->arg.line_so = ft_strdup(line + (*i + 2));
		tab->validity.if_texture_so = 1;
	}
	else
		return (ft_parse_path2(tab, line, i));
	return (SUCCESS);
}
