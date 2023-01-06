/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ends.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:26:29 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/06 21:09:08 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	the_end(t_philosopher	**recieve)
{
	t_philosopher	*philosopher;

	philosopher = *recieve;
	pthread_mutex_lock(&philosopher->end_mutex);
	if (philosopher->end == END)
		pthread_exit(NULL);
	pthread_mutex_unlock(&philosopher->end_mutex);
}

void	ende(t_timer **recieve)
{
	t_timer	*ende;
	int		number_checked;

	ende = *recieve;
	number_checked = ende->philosophers->number_of_philosophers;
	while (number_checked > 0)
	{
		pthread_mutex_lock(&ende->philosophers->end_mutex);
		ende->philosophers->end = END;
		pthread_mutex_unlock(&ende->philosophers->end_mutex);
		ende->philosophers = ende->philosophers->next;
		number_checked--;
	}
}

void	eating_ende(t_timer **recieve)
{
	t_timer	*ende;
	int		number_checked;

	ende = *recieve;
	number_checked = ende->philosophers->number_of_philosophers;
	while (number_checked > 0)
	{
		pthread_mutex_lock(&ende->philosophers->end_mutex);
		ende->philosophers->end = END;
		pthread_mutex_unlock(&ende->philosophers->end_mutex);
		ende->philosophers = ende->philosophers->next;
		number_checked--;
	}
	pthread_exit(NULL);
}
