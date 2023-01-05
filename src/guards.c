/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guards.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 20:47:12 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/04 17:18:06 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_safeguard(t_philosopher **philosopher_struct)
{
	t_philosopher	*philosopher_local;

	philosopher_local = *philosopher_struct;
	pthread_mutex_lock(&philosopher_local->hourglass->print_guard_mutex);
	if (philosopher_local->hourglass->end == END)
	{
		pthread_mutex_unlock(&philosopher_local->hourglass->print_guard_mutex);
		pthread_exit(NULL);
	}
	else
		pthread_mutex_unlock(&philosopher_local->hourglass->print_guard_mutex);
}

int	have_all_eaten(t_philosopher **table)
{
	t_philosopher	*checker;

	checker = *table;
	while (checker->indicator != LAST)
	{
		pthread_mutex_lock(&checker->eaten_full_mutex);
		if (checker->eaten_full_value == 0)
			return (0);
		pthread_mutex_unlock(&checker->eaten_full_mutex);
		checker = checker->next;
	}
	pthread_mutex_lock(&checker->eaten_full_mutex);
	if (checker->eaten_full_value == 0)
		return (0);
	pthread_mutex_unlock(&checker->eaten_full_mutex);
	return (1);
}
