/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 11:45:57 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 17:21:18 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_parser3(t_env *tab, char *line, int *i)
{
	if (line[*i] == 'F' && line[*i + 1] == ' ')
	{
		if (tab->validity.if_colors_floor == 1)
			return (ERROR_FLOOR_DUPLICATE);
		tab->arg.floor = ft_strdup(line + (*i + 1));
		tab->validity.if_colors_floor = 1;
	}
	if (line[*i] == 'C' && line[*i + 1] == ' ')
	{
		if (tab->validity.if_colors_ceil == 1)
			return (ERROR_CEIL_DUPLICATE);
		tab->arg.ceil = ft_strdup(line + (*i + 1));
		tab->validity.if_colors_ceil = 1;
	}
	return (SUCCESS);
}

int		ft_parser2(t_env *tab, char *line, int *i)
{
	if (line[*i] == 'R' && line[*i + 1] == ' ')
	{
		if (tab->validity.if_resolution == 1)
			return (ERROR_RESOLUTION_DUPLICATE);
		tab->arg.screen = ft_strdup(line + (*i + 2));
		tab->validity.if_resolution = 1;
	}
	if (ft_strchr("NWE", line[*i]) || (line[*i] == 'S' && line[*i + 1] == 'O'
			&& line[*i + 2] == ' '))
		return (ft_parse_path(tab, line, i));
	if (line[*i] == 'S' && line[*i + 1] != 'O' && line[*i + 1] == ' ')
	{
		if (tab->validity.if_texture_sprite == 1)
			return (ERROR_SPRITE_DUPLICATE);
		tab->arg.line_s = ft_strdup(line + (*i + 1));
		tab->validity.if_texture_sprite = 1;
	}
	if (line[*i] == 'F' || line[*i] == 'C')
		return (ft_parser3(tab, line, i));
	if (line[*i] == 'S' && line[*i + 1] != 'O' && line[*i + 1] != ' ')
		return (ERROR_UNKNOW_PARAM);
	return (SUCCESS);
}

int		ft_parser(t_env *tab, char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strchr("RNSWEFC", line[i]) && tab->validity.if_map_started != 1
			&& (int)ft_strlen(line) > 0)
	{
		if ((tab->error = ft_parser2(tab, line, &i)) != SUCCESS)
			return (tab->error);
	}
	else if (ft_isdigit(line[i]))
		tab->validity.if_map_started = 1;
	else if (!ft_strchr("RNSWEFC", line[i]) && !ft_isdigit(line[i]))
		return (ERROR_UNKNOW_PARAM);
	if (tab->validity.if_map_started == 1 && tab->validity.if_map != 1)
	{
		if (ft_strlen(line) == 0)
			tab->validity.if_map = 1;
		else
			return (ft_get_map(tab, line));
	}
	else if (tab->validity.if_map == 1 && ft_strlen(line) != 0)
		return (ERROR_MAP_NOT_LAST);
	return (SUCCESS);
}

void	ft_read(t_env *tab)
{
	char	*line;
	int		ret;

	if ((tab->fd = open(tab->filename, O_RDONLY)) == -1)
		ft_error(tab, ERROR_OPEN_FILE);
	while ((ret = get_next_line(tab->fd, &line)) > 0)
	{
		if (tab->error == SUCCESS)
			tab->error = ft_parser(tab, line);
		free(line);
	}
	if (line && tab->error == SUCCESS)
	{
		ft_parser(tab, line);
		free(line);
		line = NULL;
	}
	else if (tab->error != SUCCESS)
	{
		free(line);
		line = NULL;
		ft_error(tab, tab->error);
	}
	if (ret == -1)
		ft_error(tab, ERROR_READ_FILE);
}
