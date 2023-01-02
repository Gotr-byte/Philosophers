/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:50:11 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/02 18:21:14 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eating(t_philosopher **arg)
{
	t_philosopher	*philosopher;
	// time_t			get_second_fork;

	philosopher = *arg;
	pthread_mutex_lock(&philosopher->fork);
	print_safeguard(&philosopher);
	printf("%ld %d has taken a fork\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
	pthread_mutex_lock(&philosopher->next->fork);
	pthread_mutex_lock(&philosopher->hourglass->print_guard_mutex);
	if (philosopher->hourglass->end == END)
	{
		// pthread_mutex_unlock(&philosopher->next->fork);
		// pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
		pthread_exit(NULL);
	}
	else
		pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
	// get_second_fork = get_time();
	pthread_mutex_lock(&philosopher->last_eaten_mutex);
	philosopher->last_eaten = get_time();
	pthread_mutex_unlock(&philosopher->last_eaten_mutex);
	// mahlzeit = get_second_fork - philosopher->zero_time;
	pthread_mutex_lock(&philosopher->hourglass->print_guard_mutex);
	if (philosopher->hourglass->end == END)
	{
		// pthread_mutex_unlock(&philosopher->next->fork);
		// pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
	printf("%ld %d has taken a fork\n%ld %d is eating\n", \
	get_time() - philosopher->zero_time, philosopher->nb, get_time() - philosopher->zero_time, philosopher->nb);
	philosopher->sleep_time_curr = philosopher->sleep_time_set;
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
	pthread_mutex_unlock(&philosopher->hourglass->print_guard_mutex);
	printf("%ld %d is thinking\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
}