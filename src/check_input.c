/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:09:37 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/31 14:08:15 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_isdigit_char(char c)
{
	int	digit_flag;

	digit_flag = 0;
	if ((48 <= c) && (c <= 57))
		digit_flag = 1;
	return (digit_flag);
}

int	is_limit(long long int checklimit)
{
	if (checklimit > 0x7FFFFFFF)
	{
		return (2);
	}
	else
		return (0);
}

int argument_number_check(int ac, char **av)
{
	int i;
	if (ac < 5)
	{
		write(2, "Error: must enter a minunum four unsigned integer arguments\n", 61);
		return (2);
	}
	if (ac > 6)
	{
		write(2, "Error: must enter a maximum of five unsigned integer arguments\n", 64);
		return (3);
	}
	int j = 1;
	while (j < ac)
	{
		i = 0;
		while(av[j][i])
		{
			if (!(ft_isdigit_char(av[j][i])))
				{
					write(2, "Error: All agruments must be unsigned integers\n", 48);
					return(4);
				}		
			i++;
		}
		j++;
	}
	j = 1;
	while (j < ac)
	{
		if ((ft_atoi_t(av[j]) == SET_SCOPE))
		{
			write(2, "Error: Out of set scope\n", 25);
			return(6);
		}
		if ((ft_atoi_t(av[j]) == 0))
		{
			// write(2, "Error: Out of set scope\n", 25);
			return(6);
		}
		j++;
	}
	return (0);
}
