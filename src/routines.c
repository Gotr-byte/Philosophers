/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:37:16 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/02 19:43:06 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*living(void *arg)
{
	t_philosopher	*philosopher;
	int				has_eaten;

	has_eaten = 0;
	philosopher = (t_philosopher *)arg;
	while (TRUE)
	{
		eating(&philosopher);
		has_eaten++;
		if (has_eaten == philosopher->eat_times && \
		philosopher->eat_times != -1)
			{
				pthread_mutex_lock(&philosopher->eaten_full_mutex);
				philosopher->eaten_full_value = 1;
				pthread_mutex_unlock(&philosopher->eaten_full_mutex);
				pthread_mutex_lock(&philosopher->hourglass->full_philosophers_mutex);
				philosopher->hourglass->number_of_full_philosophers++;
				pthread_mutex_unlock(&philosopher->hourglass->full_philosophers_mutex);
				pthread_exit(NULL);	
			}
		sleeping(&philosopher);
		thinking(&philosopher);
	}
	return (NULL);
}

int have_all_eaten(t_philosopher **table)
{
	t_philosopher	*checker;
	
	checker = *table;
	while (checker->indicator != LAST)
	{
		pthread_mutex_lock(&checker->eaten_full_mutex);
		if(checker->eaten_full_value == 0)
			return(0);
		pthread_mutex_unlock(&checker->eaten_full_mutex);
		checker = checker->next;
	}
	pthread_mutex_lock(&checker->eaten_full_mutex);
	if(checker->eaten_full_value == 0)
		return(0);
	pthread_mutex_unlock(&checker->eaten_full_mutex);
	return (1);
}

void	*hourglass(void *timer)
{
	t_timer	*sands;

	sands = timer;
	while (TRUE)
	{
		pthread_mutex_lock(&sands->hourglass->full_philosophers_mutex);
		if (sands->philosophers->number_of_philosophers == sands->hourglass->number_of_full_philosophers)
			pthread_exit(NULL) ;
		pthread_mutex_unlock(&sands->hourglass->full_philosophers_mutex);
		while (sands->philosophers->indicator != LAST)
		{
			pthread_mutex_lock(&sands->philosophers->last_eaten_mutex);
			if (get_time() - sands->philosophers->last_eaten >= sands->philosophers->time_to_die_set && sands->philosophers->eaten_full_value == NOT_EATEN_FULL)
			{
				pthread_mutex_unlock(&sands->philosophers->last_eaten_mutex);
				pthread_mutex_lock(&sands->hourglass->print_guard_mutex);
				sands->hourglass->end = END;
				pthread_mutex_unlock(&sands->hourglass->print_guard_mutex);
				printf("%ld %d died\n", \
				get_time() - sands->philosophers->hourglass_zero_time, \
				sands->philosophers->nb);
				pthread_exit(NULL) ;
			}
			else
			{
				pthread_mutex_unlock(&sands->philosophers->last_eaten_mutex);
				sands->philosophers = sands->philosophers->next;
			}
		}
		pthread_mutex_lock(&sands->philosophers->last_eaten_mutex);
		if (get_time() - sands->philosophers->last_eaten >= sands->philosophers->time_to_die_set && sands->philosophers->eaten_full_value == NOT_EATEN_FULL)
		{
			pthread_mutex_unlock(&sands->philosophers->last_eaten_mutex);
			pthread_mutex_lock(&sands->hourglass->print_guard_mutex);
			sands->hourglass->end = END;
			pthread_mutex_unlock(&sands->hourglass->print_guard_mutex);
			printf("%ld %d has died\n", \
			get_time() - sands->philosophers->hourglass_zero_time, \
			sands->philosophers->nb);
			pthread_exit(NULL) ;
		}
		else
		{
			pthread_mutex_unlock(&sands->philosophers->last_eaten_mutex);
			sands->philosophers = sands->philosophers->next;
		}
		usleep (1000);
	}
}
			