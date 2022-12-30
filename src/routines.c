/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:37:16 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/30 18:41:48 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eating(t_philosopher **arg)
{
	t_philosopher	*philosopher;
	time_t			get_second_fork;
	time_t			mahlzeit;
	time_t			target_eat_time;
	
	philosopher = *arg;
	pthread_mutex_lock(&philosopher->fork);
	print_safeguard(&philosopher);
	printf("%ld %d has taken a fork\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
	pthread_mutex_lock(&philosopher->next->fork);
	pthread_mutex_lock(&philosopher->end);
	if (philosopher->hourglass->end == END)
	{
		pthread_mutex_unlock(&philosopher->next->fork);
		pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(&philosopher->end);
		printf("Exited before first fork\n");
		pthread_exit(NULL);
	}
	else
		pthread_mutex_unlock(&philosopher->end);
	get_second_fork = get_time();
	pthread_mutex_lock(&philosopher->last_eaten_mutex);
	philosopher->last_eaten = get_second_fork;
	pthread_mutex_unlock(&philosopher->last_eaten_mutex);
	mahlzeit = get_second_fork - philosopher->zero_time;
	pthread_mutex_lock(&philosopher->end);
	if (philosopher->hourglass->end == END)
	{
		pthread_mutex_unlock(&philosopher->next->fork);
		pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(&philosopher->end);
		printf("Exited before second fork\n");
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philosopher->end);
	printf("%ld %d has taken a fork\n%ld %d is eating\n", \
	mahlzeit, philosopher->nb, mahlzeit, philosopher->nb);
	philosopher->sleep_time_curr = philosopher->sleep_time_set;
	target_eat_time = get_time() + philosopher->gorge_time;
	philosopher_do(&philosopher, target_eat_time);
	pthread_mutex_unlock(&philosopher->next->fork);
	pthread_mutex_unlock(&philosopher->fork);
}

void	sleeping(t_philosopher **arg)
{
	t_philosopher	*philosopher;
	time_t			target_sleep_time;

	philosopher = *arg;
	target_sleep_time = get_time() + philosopher->sleep_time_set;
	pthread_mutex_lock(&philosopher->end);
	if (philosopher->hourglass->end == END)
	{
		pthread_mutex_unlock(&philosopher->end);
		printf("Exited befor sleeping\n");
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philosopher->end);
	printf("%ld %d is sleeping\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
	philosopher_do (&philosopher, target_sleep_time);
}

void	thinking(t_philosopher **arg)
{
	t_philosopher	*philosopher;
	
	philosopher = *arg;
	pthread_mutex_lock(&philosopher->end);
	if (philosopher->hourglass->end == END)
	{
		pthread_mutex_unlock(&philosopher->end);
		printf("Exited before thinking\n");
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philosopher->end);
	printf("%ld %d is thinking\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
}

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
			pthread_exit(NULL);
		sleeping(&philosopher);
		thinking(&philosopher);
	}
	return (NULL);
}

void	hourglass(t_philosopher **table, t_hourglass **hourglass_recieve)
{
	t_philosopher	*sands;
	t_hourglass		*point_to_hourglass;

	sands = *table;
	point_to_hourglass = *hourglass_recieve;
	while (TRUE)
	{
		while (sands->indicator != LAST)
		{
			pthread_mutex_lock(&sands->last_eaten_mutex);
			if (get_time() - sands->last_eaten >= sands->time_to_die_set)
			{
				pthread_mutex_unlock(&sands->last_eaten_mutex);
				pthread_mutex_lock(&sands->end);
				point_to_hourglass->end = END;
				printf("%ld %d has died\n", \
				get_time() - sands->hourglass_zero_time, \
				sands->nb);
				pthread_mutex_unlock(&sands->end);
				pthread_mutex_unlock(&sands->fork);
				pthread_mutex_unlock(&sands->next->fork);
				return ;
			}
			else
			{
				pthread_mutex_unlock(&sands->last_eaten_mutex);
				usleep (1000);
				sands = sands->next;	
			}
		}
		pthread_mutex_lock(&sands->last_eaten_mutex);
		if (get_time() - sands->last_eaten >= sands->time_to_die_set)
		{
			pthread_mutex_unlock(&sands->last_eaten_mutex);
			pthread_mutex_lock(&sands->end);
			point_to_hourglass->end = END;
			printf("%ld %d has died\n", \
			get_time() - sands->hourglass_zero_time, \
			sands->nb);
			pthread_mutex_unlock(&sands->end);
			return ;
		}
		pthread_mutex_unlock(&sands->last_eaten_mutex);
		usleep (1000);
		sands = sands->next;
	}
}