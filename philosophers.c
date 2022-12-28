/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/28 15:59:48 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Needs a function to check if everyone has eaten.

*/
#include "./philosophers.h"

long	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	eating(t_philosopher **arg)
{
	t_philosopher	*philosopher;
	time_t			get_second_fork;
	time_t			mahlzeit;
	time_t			target_eat_time;

	philosopher = *arg;
	pthread_mutex_lock(&philosopher->fork);
	printf("%ld %d has taken a fork\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
	pthread_mutex_lock(&philosopher->next->fork);
	get_second_fork = get_time();
	// pthread_mutex_lock(&philosopher->is_dead);
	philosopher->last_eaten = get_second_fork;
	// pthread_mutex_unlock(&philosopher->is_dead);
	mahlzeit = get_second_fork - philosopher->zero_time;
	printf("%ld %d has taken a fork\n%ld %d is eating\n", \
	mahlzeit, philosopher->nb, mahlzeit, philosopher->nb);
	philosopher->sleep_time_curr = philosopher->sleep_time_set;
	target_eat_time = get_time() + philosopher->gorge_time;
	while (get_time() < target_eat_time)
		usleep(100);
	pthread_mutex_unlock(&philosopher->next->fork);
	pthread_mutex_unlock(&philosopher->fork);
}

void	sleeping(t_philosopher **arg)
{
	t_philosopher	*philosopher;
	time_t			target_sleep_time;

	philosopher = *arg;
	// printf("philosopher->sleep_time_set: %d\n", philosopher->sleep_time_set);
	target_sleep_time = get_time() + philosopher->sleep_time_set;
	printf("%ld %d is sleeping\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
	// usleep(philosopher->sleep_time_curr);
	// philosopher->sleep_time_curr = 0;
	
	while (get_time() < target_sleep_time)
	{
		usleep(100);
		// printf("currenttime: %ld\n", get_time());
		// printf("targettime: %ld\n", targettime);
	}
}



void	thinking(t_philosopher **arg)
{
	t_philosopher	*philosopher;

	philosopher = *arg;
	printf("%ld %d is thinking\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
}

void	*living(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (TRUE)
	{
		eating(&philosopher);
		sleeping(&philosopher);
		thinking(&philosopher);
	}
	return (NULL);
}

void	hourglass(t_philosopher **table)
{
	t_philosopher	*sands;

	sands = *table;
	// pthread_mutex_lock(&sands->is_dead);
	if (get_time() - sands->last_eaten >= sands->time_to_die_set)
	{
		printf("%ld %d has died\n", \
		get_time() - sands->hourglass_zero_time, \
		sands->nb);
		// expell_mutexes(table);
		// release_list(table);
		exit(0);
	}
	sands = sands->next;
	usleep (1000);
	// pthread_mutex_unlock(&sands->is_dead);
}

//waiter function placeholder
// void	*waiter(void *)

int	main(int ac, char **av)
{
	int				i;
	t_philosopher	*table;

	table = NULL;
	printf("%ld Start time\n", get_time());
	if (ac == 1)
		exit(2);
	i = 1;
	while (i <= ft_atoi(av[1]))
	{
		local_lstadd_back(&table, ft_lstnew_int(i, ft_atoi(av[2]), \
		ft_atoi(av[3]), ft_atoi(av[4])));
		i++;
	}
	last_point_first(&table);
	traverse_table(&table, get_time());
	summon_mutexes(&table);
	weave_threads(&table);
	// while (TRUE)
	// 	hourglass(&table);
	join_threads(&table);
	expell_mutexes(&table);
	release_list(&table);
	return (0);
}
