/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:07:08 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/30 18:59:00 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_wh_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '	' || str[i] == '\t' \
	|| str[i] == '\n' || str[i] == '\v' \
	|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

unsigned int	ft_atoi_uint(const char *str)
{
	int	val[4];

	val[0] = ft_wh_space((char *)str);
	val[1] = 0;
	val[2] = 1;
	val[3] = 0;
	if (str[val[0]] == '-')
		val[2] = -1;
	if (str[val[0]] == '-' || str[val[0]] == '+')
	{
		val[0]++;
		if (str[val[0] + 1] == '-' || str[val[0] + 1] == '+')
			return (0);
	}
	while (((*(str + val[0])) >= 48) && ((*(str + val[0])) <= 57))
	{
		val[1] = 10 * val[1] + (int)(*(str + val[0]) - 48);
		val[3] = 1;
		val[0]++;
	}
	if (val[3] != 0)
		return (val[2] * val[1]);
	return (0);
}

static void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*pt;

	pt = s;
	i = 0;
	while (i < n)
	{
			pt[i] = 0;
			i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*point_to_calloc;
	size_t	t;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	t = count * size;
	point_to_calloc = malloc(t);
	if (!point_to_calloc)
		return (NULL);
	ft_bzero(point_to_calloc, t);
	return (point_to_calloc);
}
