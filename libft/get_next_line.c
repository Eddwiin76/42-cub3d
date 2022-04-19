/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:17:19 by tpierre           #+#    #+#             */
/*   Updated: 2020/05/28 19:13:39 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_exitprogram(char **data, char **bufforline)
{
	free(*data);
	free(*bufforline);
	return (-1);
}

int		ft_copy(char **data, char **line)
{
	char		*tmp;
	int			i;

	if (ft_strchr(*data, '\n'))
	{
		i = 0;
		while ((*data)[i] != '\n')
			i++;
		if ((*line = ft_substr(*data, 0, i)) == NULL
			|| (tmp = ft_strdup(*data + i + 1)) == NULL)
			return (ft_exitprogram(data, line));
		free(*data);
		*data = tmp;
		return (1);
	}
	else
	{
		if ((*line = ft_strdup(*data)) == NULL)
			return (ft_exitprogram(data, NULL));
		free(*data);
		*data = NULL;
		return (0);
	}
}

int		get_next_line(int fd, char **line)
{
	static char	*data[9999];
	int			len;
	char		*buff;
	char		*tmp;

	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	if (data[fd] == NULL)
		if ((data[fd] = ft_strdup("")) == NULL)
			return (ft_exitprogram(NULL, &buff));
	while (!(ft_strchr(data[fd], '\n'))
		&& (len = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[len] = '\0';
		if ((tmp = ft_strjoin(data[fd], buff)) == NULL)
			return (ft_exitprogram(&data[fd], &buff));
		free(data[fd]);
		data[fd] = tmp;
	}
	free(buff);
	return (ft_copy(&data[fd], line));
}
