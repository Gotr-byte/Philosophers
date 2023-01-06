/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guards.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 20:47:12 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/06 19:27:53 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	befork_safeguard(t_philosopher **philosopher_struct)
{
	t_philosopher	*philosopher_local;

	philosopher_local = *philosopher_struct;
	
	pthread_mutex_lock(&philosopher_local->end_mutex);
	if (philosopher_local->end == END)
	{
		pthread_mutex_unlock(&philosopher_local->end_mutex);
		pthread_mutex_unlock(&philosopher_local->fork);
		pthread_exit(NULL);
	}
	else
	{
		printf("%ld %d has taken a fork\n", \
		get_time() - philosopher_local->zero_time, \
		philosopher_local->nb);
		pthread_mutex_unlock(&philosopher_local->end_mutex);
	}
}

void	print_safeguard(t_philosopher **philosopher_struct)
{
	t_philosopher	*philosopher_local;

	philosopher_local = *philosopher_struct;
	pthread_mutex_lock(&philosopher_local->end_mutex);
	if (philosopher_local->end == END)
	{
		pthread_mutex_unlock(&philosopher_local->end_mutex);
		pthread_mutex_unlock(&philosopher_local->fork);
		pthread_exit(NULL);
	}
	else
	{
		printf("%ld %d has taken a fork\n", \
		get_time() - philosopher_local->zero_time, \
		philosopher_local->nb);
		pthread_mutex_unlock(&philosopher_local->end_mutex);
	}
}

// int	have_all_eaten(t_philosopher **table)
// {
// 	t_philosopher	*checker;

// 	checker = *table;
// 	while (checker->indicator != LAST)
// 	{
// 		pthread_mutex_lock(&checker->eaten_full_mutex);
// 		if (checker->eaten_full_value == 0)
// 			return (0);
// 		pthread_mutex_unlock(&checker->eaten_full_mutex);
// 		checker = checker->next;
// 	}
// 	pthread_mutex_lock(&checker->eaten_full_mutex);
// 	if (checker->eaten_full_value == 0)
// 		return (0);
// 	pthread_mutex_unlock(&checker->eaten_full_mutex);
// 	return (1);
// }

void	eating_safeguard(t_philosopher **recieve)
{
	t_philosopher	*philosopher;

	philosopher = *recieve;
	pthread_mutex_lock(&philosopher->end_mutex);
	if (philosopher->end == END)
	{
		pthread_mutex_unlock(&philosopher->end_mutex);
		pthread_mutex_unlock(&philosopher->next->fork);
		pthread_mutex_unlock(&philosopher->fork);
		pthread_exit(NULL);
	}
	else
	{
		printf("%ld %d has taken a fork\n%ld %d is eating\n", \
		get_time() - philosopher->zero_time, philosopher->nb, \
		get_time() - philosopher->zero_time, philosopher->nb);
		pthread_mutex_unlock(&philosopher->end_mutex);
	}
}
