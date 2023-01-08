/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_rev.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:20:11 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/08 20:25:18 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	start_offset(t_philosopher **recieve)
{
	t_philosopher	*philosopher;

	philosopher = *recieve;
	while (philosopher->start == 0 && \
	get_time() <= philosopher->zero_time)
	{
	}
	if (philosopher->start == 0 && philosopher->nb % 2 != 0)
	{
		usleep(250);
		philosopher->start = 1;
	}
}

void	have_they_consumed(t_philosopher **recieve, int has_consumed)
{
	t_philosopher	*philosopher;

	philosopher = *recieve;
	if (philosopher->eat_times != -1 && \
	has_consumed == philosopher->eat_times)
	{
		pthread_mutex_lock(&philosopher->eaten_full_mutex);
		philosopher->eaten_full_value = 1;
		pthread_mutex_unlock(&philosopher->eaten_full_mutex);
		philosopher->eat_times = -1;
	}
}

void	*living(void *arg)
{
	t_philosopher	*philosopher;
	int				has_eaten;

	philosopher = (t_philosopher *)arg;
	start_offset(&philosopher);
	has_eaten = 0;
	while (TRUE)
	{
		the_end(&philosopher);
		eating(&philosopher);
		has_eaten++;
		have_they_consumed(&philosopher, has_eaten);
		sleeping(&philosopher);
		thinking(&philosopher);
	}
	return (NULL);
}

static void	did_one_die(t_timer **recieve)
{
	t_timer	*sands;

	sands = *recieve;
	pthread_mutex_lock(&sands->philosophers->last_eaten_mutex);
	if (get_time() - sands->philosophers->last_eaten >= \
	sands->time_to_die && \
	sands->philosophers->eaten_full_value == NOT_EATEN_FULL)
	{
		pthread_mutex_unlock(&sands->philosophers->last_eaten_mutex);
		ende(&sands);
		printf("%ld %d died\n", \
		get_time() - sands->timer_zero_time, \
		sands->philosophers->nb);
		pthread_exit(NULL);
	}
	else
	{
		pthread_mutex_unlock(&sands->philosophers->last_eaten_mutex);
		sands->philosophers = sands->philosophers->next;
	}
}

void	*hourglass(void *timer)
{
	t_timer	*sands;
	int		check_times;
	int		number_of_philos_eaten_full;

	sands = timer;
	while (get_time() <= sands->timer_zero_time)
		usleep(1);
	while (TRUE)
	{
		check_times = sands->philosophers->number_of_philosophers;
		number_of_philos_eaten_full = 0;
		while (check_times > 0)
		{
			did_one_die(&sands);
			pthread_mutex_lock(&sands->philosophers->eaten_full_mutex);
			if (sands->philosophers->eaten_full_value == 1)
				number_of_philos_eaten_full++;
			pthread_mutex_unlock(&sands->philosophers->eaten_full_mutex);
			if (sands->number_of_philosophers_in_timer == \
			number_of_philos_eaten_full)
				eating_ende(&sands);
			check_times--;
		}
		usleep (8000);
	}
}
