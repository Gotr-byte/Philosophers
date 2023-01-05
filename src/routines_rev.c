/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_rev.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:20:11 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/05 19:57:23 by pbiederm         ###   ########.fr       */
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
		usleep(1250);
		philosopher->start = 1;
	}
}

void	have_they_consumed(t_philosopher **recieve, int has_consumed)
{
	t_philosopher	*philosopher;

	philosopher = *recieve;
	if (has_consumed == philosopher->eat_times && \
	philosopher->eat_times != -1)
	{
		pthread_mutex_lock(&philosopher->eaten_full_mutex);
		philosopher->eaten_full_value = 1;
		pthread_mutex_unlock(&philosopher->eaten_full_mutex);
		pthread_mutex_lock(&philosopher->\
		hourglass->full_philosophers_mutex);
		philosopher->hourglass->number_of_full_philosophers++;
		pthread_mutex_unlock(&philosopher->\
		hourglass->full_philosophers_mutex);
		pthread_exit(NULL);
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
	sands->philosophers->time_to_die_set && \
	sands->philosophers->eaten_full_value == NOT_EATEN_FULL)
	{
		pthread_mutex_unlock(&sands->philosophers->last_eaten_mutex);
		pthread_mutex_lock(&sands->hourglass->print_guard_mutex);
		sands->hourglass->end = END;
		pthread_mutex_unlock(&sands->hourglass->print_guard_mutex);
		printf("%ld %d died\n", \
		get_time() - sands->philosophers->hourglass_zero_time, \
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

	sands = timer;
	while (get_time() <= sands->hourglass->hourglass_zero_time)
	{
	}
	while (TRUE)
	{
		check_times = sands->philosophers->number_of_philosophers;
		pthread_mutex_lock(&sands->hourglass->full_philosophers_mutex);
		if (sands->philosophers->number_of_philosophers == \
		sands->hourglass->number_of_full_philosophers)
			pthread_exit(NULL);
		pthread_mutex_unlock(&sands->hourglass->full_philosophers_mutex);
		while (check_times >= 0)
		{
			did_one_die(&sands);
			check_times--;
		}
		usleep (2000);
	}
}
