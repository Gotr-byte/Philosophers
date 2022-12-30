/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/29 20:06:29 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Needs a function to check if everyone has eaten.

*/
#include "../includes/philosophers.h"

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
	int				end;

	end = NOT_END;
	philosopher = *arg;
	pthread_mutex_lock(&philosopher->fork);
	printf("%ld %d has taken a fork\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
	pthread_mutex_lock(&philosopher->next->fork);
	get_second_fork = get_time();
	pthread_mutex_lock(&philosopher->is_dead);
	philosopher->last_eaten = get_second_fork;
	pthread_mutex_unlock(&philosopher->is_dead);
	mahlzeit = get_second_fork - philosopher->zero_time;
	printf("%ld %d has taken a fork\n%ld %d is eating\n", \
	mahlzeit, philosopher->nb, mahlzeit, philosopher->nb);
	philosopher->sleep_time_curr = philosopher->sleep_time_set;
	target_eat_time = get_time() + philosopher->gorge_time;
	// pthread_mutex_lock(&philosopher->end);
	// while (get_time() < target_eat_time &&  philosopher->hourglass->end)
	while (get_time() < target_eat_time)
	{
		// if	(philosopher->hourglass->end == 0)
		// 	pthread_exit(0);
		// pthread_mutex_unlock(&philosopher->end);
		usleep(100);
		// pthread_mutex_lock(&philosopher->end);
	}
	// pthread_mutex_unlock(&philosopher->end);
	pthread_mutex_unlock(&philosopher->next->fork);
	pthread_mutex_unlock(&philosopher->fork);
}

void	sleeping(t_philosopher **arg)
{
	t_philosopher	*philosopher;
	time_t			target_sleep_time;

	philosopher = *arg;
	target_sleep_time = get_time() + philosopher->sleep_time_set;
	printf("%ld %d is sleeping\n", \
	get_time() - philosopher->zero_time, \
	philosopher->nb);
	while (get_time() < target_sleep_time && philosopher->hourglass->end == NOT_END)
	{
		usleep(100);
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
	int				has_eaten;

	has_eaten = 0;
	philosopher = (t_philosopher *)arg;
	while (TRUE)
	{
		eating(&philosopher);
		has_eaten++;
		// printf("philosopher %d has eaten %d times\n", philosopher->nb, has_eaten);
		if (has_eaten == philosopher->eat_times)
			break;
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
	pthread_mutex_lock(&sands->is_dead);
	if (get_time() - sands->last_eaten >= sands->time_to_die_set)
	{
		// pthread_mutex_lock(&sands->end);
		point_to_hourglass->end = END;
		// pthread_mutex_unlock(&sands->end);
		printf("%ld %d has died\n", \
		get_time() - sands->hourglass_zero_time, \
		sands->nb);
		join_threads(table);
		release_list(table);
		free(*hourglass_recieve);
		exit(0);
	}
	pthread_mutex_unlock(&sands->is_dead);
	usleep (100);
	sands = sands->next;
}

int	main(int ac, char **av)
{
	int				i;
	t_philosopher	*table;
	t_hourglass		*point_to_hourglass;

	table = NULL;
	point_to_hourglass = NULL;
	point_to_hourglass = ft_calloc(1, sizeof(t_hourglass));
	point_to_hourglass->end = NOT_END;
	printf("%ld Start time\n", get_time());
	if (ac == 1)
		exit(2);
	i = 1;
	while (i <= ft_atoi(av[1]))
	{
		local_lstadd_back(&table, ft_lstnew_int(i, ft_atoi(av[2]), \
		ft_atoi(av[3]), ft_atoi(av[4]), ft_atoi(av[5]), &point_to_hourglass));
		i++;
	}
	last_point_first(&table);
	traverse_table(&table, get_time());
	summon_mutexes(&table);
	weave_threads(&table);
	while (TRUE)
		hourglass(&table, &point_to_hourglass);
	join_threads(&table);
	expell_mutexes(&table);
	release_list(&table);
	return (0);
}
