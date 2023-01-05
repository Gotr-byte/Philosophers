/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:50:11 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/05 18:47:46 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eating_safeguard(t_philosopher **recieve)
{
	t_philosopher	*philosopher;

	philosopher = *recieve;
	pthread_mutex_lock(&philosopher->hourglass->print_guard_mutex);
	if (philosopher->hourglass->end == END)
	{
		pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
		pthread_mutex_unlock(&philosopher->next->fork);
		pthread_mutex_unlock(&philosopher->fork);
		pthread_exit(NULL);
	}
	else
	{
		printf("%ld %d has taken a fork\n%ld %d is eating\n", \
		get_time() - philosopher->zero_time, philosopher->nb, \
		get_time() - philosopher->zero_time, philosopher->nb);
		pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
	}
}

void	eating(t_philosopher **arg)
{
	t_philosopher	*philosopher;

	philosopher = *arg;
	pthread_mutex_lock(&philosopher->fork);
	print_safeguard(&philosopher);
	pthread_mutex_lock(&philosopher->next->fork);
	pthread_mutex_lock(&philosopher->last_eaten_mutex);
	philosopher->last_eaten = get_time();
	pthread_mutex_unlock(&philosopher->last_eaten_mutex);
	eating_safeguard(&philosopher);
	philosopher_do(&philosopher);
	pthread_mutex_unlock(&philosopher->next->fork);
	pthread_mutex_unlock(&philosopher->fork);
}

void	sleeping(t_philosopher **arg)
{
	t_philosopher	*philosopher;
	time_t			target_sleep_time;

	philosopher = *arg;
	target_sleep_time = get_time() + philosopher->sleep_time_set;
	pthread_mutex_lock(&philosopher->hourglass->print_guard_mutex);
	if (philosopher->hourglass->end == END)
	{
		pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
	printf("%ld %d is sleeping\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
	philosopher_sleep (&philosopher, target_sleep_time);
}

void	thinking(t_philosopher **arg)
{
	t_philosopher	*philosopher;


	philosopher = *arg;
	pthread_mutex_lock(&philosopher->hourglass->print_guard_mutex);
	if (philosopher->hourglass->end == END)
	{
		pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
		pthread_exit(NULL);
	}
	else
	{
		printf("%ld %d is thinking\n", \
		get_time() - philosopher->zero_time, \
		philosopher->nb);
		pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
	}
}

void	philosopher_do(t_philosopher **philosopher)
{
	t_philosopher	*philosopher_doing;
	long			x_time;

	philosopher_doing = *philosopher;
	x_time = get_time() + philosopher_doing->gorge_time;
	while (get_time() < x_time)
	{
		pthread_mutex_lock(&philosopher_doing->hourglass->print_guard_mutex);
		if (philosopher_doing->hourglass->end == END)
		{
			pthread_mutex_unlock(&philosopher_doing->\
			hourglass->print_guard_mutex);
			pthread_mutex_unlock(&philosopher_doing->next->fork);
			pthread_mutex_unlock(&philosopher_doing->fork);
			pthread_exit(NULL);
		}
		else
		{
			pthread_mutex_unlock(&philosopher_doing->\
			hourglass->print_guard_mutex);
			usleep(100);
		}
	}
}

void	philosopher_sleep(t_philosopher **philosopher, long x_time)
{
	t_philosopher	*philosopher_doing;

	philosopher_doing = *philosopher;
	while (get_time() < x_time)
	{
		pthread_mutex_lock(&philosopher_doing->hourglass->print_guard_mutex);
		if (philosopher_doing->hourglass->end == END)
		{
			pthread_mutex_unlock(&philosopher_doing->\
			hourglass->print_guard_mutex);
			pthread_exit(NULL);
		}
		else
		{
			pthread_mutex_unlock(&philosopher_doing->\
			hourglass->print_guard_mutex);
			usleep(100);
		}
	}
}
