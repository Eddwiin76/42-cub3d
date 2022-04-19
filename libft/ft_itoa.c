/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:17:54 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/09 01:44:42 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoasize(int n)
{
	int i;

	i = 0;
	if (n == -2147483648)
		return (11);
	else if (n == 0)
		return (1);
	else if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*itoacpy(char *s, int n, int size, int i)
{
	if (i == 1)
	{
		*s = '-';
		n = -n;
		size++;
	}
	if (n == 0)
		s[i++] = '0';
	i++;
	while (n)
	{
		s[size - i++] = (n % 10) + 48;
		n = n / 10;
	}
	s[i - 1] = '\0';
	return (s);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		size;
	int		i;

	size = itoasize(n);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (n == -2147483648)
		return (s = ft_memcpy(s, "-2147483648\0", 12));
	else if (n < 0)
		i = 1;
	else
		i = 0;
	s = itoacpy(s, n, size, i);
	return (s);
}
