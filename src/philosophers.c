/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/30 16:08:53 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Needs a function to check if everyone has eaten.

*/
#include "../includes/philosophers.h"

void	philosopher_do(t_philosopher **philosopher, long x_time)
{
	t_philosopher	*philosopher_doing;

	philosopher_doing = *philosopher;
	while (get_time() < x_time)
	{
		pthread_mutex_lock(&philosopher_doing->end);
		if (philosopher_doing->hourglass->end == END)
		{
			// pthread_mutex_unlock(&philosopher_doing->next->fork);
			// pthread_mutex_unlock(&philosopher_doing->fork);
			// pthread_mutex_unlock(&philosopher_doing->fork);
			pthread_mutex_unlock(&philosopher_doing->end);
			printf("This is the end of thread %d\n", philosopher_doing->nb);
			pthread_exit(NULL);
		}
		else
			pthread_mutex_unlock(&philosopher_doing->end);
		usleep(100);
	}
}

void	print_safeguard(t_philosopher **philosopher_struct)
{
	t_philosopher	*philosopher_local;

	philosopher_local = *philosopher_struct;
	pthread_mutex_lock(&philosopher_local->end);
	if (philosopher_local->hourglass->end == END)
	{
		// pthread_mutex_unlock(&philosopher_local->next->fork);
		pthread_mutex_unlock(&philosopher_local->fork);
		pthread_mutex_unlock(&philosopher_local->end);
		printf("Exited before second fork\n");
		pthread_exit(NULL);
	}
	else
		pthread_mutex_unlock(&philosopher_local->end);
}
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
	// pthread_mutex_lock(&philosopher->end);
	// if (philosopher->hourglass->end == END)
	// {
	// 	pthread_mutex_unlock(&philosopher->end);
	// 	printf("Exited before first fork\n");
	// 	pthread_exit(NULL);
	// }
	// pthread_mutex_unlock(&philosopher->end);
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
		if (has_eaten == philosopher->eat_times)
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
				// pthread_mutex_lock(&sands->end);
				// 	if (sands->hourglass->end == END)
				// 	{
				// 		pthread_mutex_unlock(&sands->end);
				// 		printf("Exited before dying\n");
				// 		return ;
				// 	}
				// pthread_mutex_unlock(&sands->end);
				pthread_mutex_lock(&sands->end);
				point_to_hourglass->end = END;
				pthread_mutex_unlock(&sands->end);
				printf("%ld %d has died\n", \
				get_time() - sands->hourglass_zero_time, \
				sands->nb);
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
			// pthread_mutex_lock(&sands->end);
			// if (sands->hourglass->end == END)
			// {
			// 	pthread_mutex_unlock(&sands->end);
			// 	printf("Exited before thinking\n");
			// 	return 	;
			// }
			// pthread_mutex_unlock(&sands->end);
			pthread_mutex_lock(&sands->end);
			point_to_hourglass->end = END;
			pthread_mutex_unlock(&sands->end);
			printf("%ld %d has died\n", \
			get_time() - sands->hourglass_zero_time, \
			sands->nb);
			return ;
		}
		pthread_mutex_unlock(&sands->last_eaten_mutex);
		usleep (1000);
		sands = sands->next;
	}
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
	hourglass(&table, &point_to_hourglass);
	join_threads(&table);
	expell_mutexes(&table);
	release_list(&table);
	return (0);
}
