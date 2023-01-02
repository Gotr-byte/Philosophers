/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:08:00 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/02 18:28:11 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*Hardcoded situation when there is one philosopher
 who picks up the fork and dies of starvation*/
int	single_philosopher(char **av)
{
	if (ft_atoi_t(av[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi_t(av[2]) * 1000);
		printf("%lld 1 died\n", ft_atoi_t(av[2]));
		return (1);
	}
	return (0);
}