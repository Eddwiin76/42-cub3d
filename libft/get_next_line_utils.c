/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:17:12 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/12 17:45:44 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*dst;

	if (!(dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	if ((!s) || (!(dst = (char *)malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	if (start > ft_strlen(s))
	{
		free(dst);
		return (ft_strdup(""));
	}
	i = 0;
	while (i < len && s[start])
		dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}

char		*ft_strcat(char *s1, const char *s2)
{
	char *s3;

	s3 = s1;
	while (*s3)
		s3++;
	while (*s2)
		*s3++ = *s2++;
	*s3 = '\0';
	return (s1);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		lens1ands2;
	char	*dst;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1ands2 = ft_strlen(s1) + ft_strlen(s2);
	if (!(dst = (char *)malloc(sizeof(char) * (lens1ands2 + 1))))
		return (NULL);
	i = 0;
	while (i < (lens1ands2 + 1))
		dst[i++] = 0;
	dst = ft_strcat(dst, s1);
	dst = ft_strcat(dst, s2);
	return (dst);
}
