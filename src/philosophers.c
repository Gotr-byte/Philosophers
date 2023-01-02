/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/02 19:46:06 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Needs a function to check if everyone has eaten.
*/
#include "../includes/philosophers.h"

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

int	main(int ac, char **av)
{
	t_philosopher	*table;
	t_hourglass		*point_to_hourglass;
	t_timer			*reaper;

	table = NULL;
	point_to_hourglass = NULL;
	reaper = NULL;
	reaper = malloc(sizeof(reaper));
	reaper->id = 42;
	if (argument_number_check(ac, av) != 0)
		return (2);
	if (single_philosopher(av))
		return (0);
	point_to_hourglass = initialize_hourglass(point_to_hourglass);
	table = initialization_step(ac, av, table, point_to_hourglass);
	reaper->philosophers = table;
	reaper->hourglass = point_to_hourglass;
	pthread_create(&reaper->id, NULL, hourglass, reaper);
	weave_threads(&table);
	join_threads(&table);
	pthread_join(reaper->id, NULL);
	expell_mutexes(&table);
	release_list(&table, point_to_hourglass, reaper);
	return (0);
}
