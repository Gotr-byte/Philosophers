/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/31 19:12:58 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

long get_time(void)
{
	struct	timeval	tp;
	long	miliseconds;

	gettimeofday(&tp, NULL);
	miliseconds = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (miliseconds);
}

void *eating(void *arg)
{
	t_philosopher 	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (TRUE)
	{
		// if(philosopher->nb % 2 != 0 && philosopher->sleep_time_curr == 0)
		// {
		// 	pthread_mutex_lock(&philosopher->next->fork);
		// 	printf("%ld %d picked up a fork\n",\
		// 	get_time()- philosopher->zero_time,\
		// 	philosopher->nb);
		// 	pthread_mutex_lock(&philosopher->fork);
		// 	printf("%ld %d picked up a fork\n",\
		// 	get_time()- philosopher->zero_time,\
		// 	philosopher->nb);
		// 	philosopher->sleep_time_curr = philosopher->sleep_time_set;
		// 	printf("%ld %d is eating\n",\
		// 	get_time() - philosopher->zero_time,\
		// 	philosopher->nb);
		// 	philosopher->last_eaten = get_time();
		// 	usleep(philosopher->gorge_time);
		// 	while(philosopher->gorge_time--)
		// 		usleep(1000);
		// 	pthread_mutex_unlock(&philosopher->fork);
		// 	pthread_mutex_unlock(&philosopher->next->fork);
		// }
		// if(philosopher->nb %2 == 0 && philosopher->sleep_time_curr == 0)
		// printf("last eaten %ld\n", philosopher->last_eaten);
		// printf("time to die set %d\n", philosopher->time_to_die_set);
		// printf("get_time() - table->last_eaten: %ld\n ", get_time() - philosopher->last_eaten);
		// if(philosopher->sleep_time_curr == 0)
		// {
		// pthread_mutex_lock(&philosopher->next->fork);
		pthread_mutex_lock(&philosopher->fork);
		printf("%ld %d picked up a fork\n",\
		get_time()- philosopher->zero_time,\
		philosopher->nb);
		// pthread_mutex_unlock(&philosopher->next->fork);
		pthread_mutex_lock(&philosopher->next->fork);
		printf("%ld %d picked up a fork\n",\
		get_time()- philosopher->zero_time,\
		philosopher->nb);
		philosopher->sleep_time_curr = philosopher->sleep_time_set;
		printf("%ld %d is eating\n",\
		get_time()- philosopher->zero_time,\
		philosopher->nb);
		philosopher->last_eaten = get_time();
		usleep(philosopher->gorge_time);
		pthread_mutex_unlock(&philosopher->next->fork);
		pthread_mutex_unlock(&philosopher->fork);
		// }
		if (philosopher->sleep_time_curr > 0)
		{
			printf("%ld %d is sleeping\n", \
			get_time()- philosopher->zero_time,\
			philosopher->nb);
			usleep(philosopher->sleep_time_curr);
			philosopher->sleep_time_curr = 0;
			printf("%ld %d is taking his time thinking\n", \
			get_time()- philosopher->zero_time,\
			philosopher->nb);
		}
	}
	return (NULL);
}

int main (int	ac, char **av)
{
	int				i;
	t_philosopher	*table;
	// pthread_t		squeaker_id;
	// int				*end;
	
	// struct timeval	start;
	printf("%ld Start time\n", get_time());
	if (ac == 1)
		exit(2);
	i = 1;
	while	(i <= ft_atoi(av[1]))
	{
		local_lstadd_back(&table, ft_lstnew_int(i, ft_atoi(av[2]), \
		ft_atoi(av[3]), ft_atoi(av[4]), ft_atoi(av[5])));
		i++;
	}
	last_point_first(&table);
	// gettimeofday(&start, NULL);
	traverse_table(&table, get_time());
	summon_mutexes(&table);
	weave_threads(&table);
	// pthread_create(&squeaker_id, NULL, grim_squeaker, table);
	// pthread_join(squeaker_id, (void**)&end);
	// usleep(300);
	while(TRUE)
	{
		if (get_time() - table->last_eaten >= table->time_to_die_set)
			{
				// printf("last eaten %ld\n", table->last_eaten);
				// printf("time to die set %d\n", table->time_to_die_set);
				// printf("get_time() - table->last_eaten: %ld\n ", get_time() - table->last_eaten);
				printf("%ld %d has died\n", \
				get_time() - table->zero_time,\
				table->nb);
				exit(0);
			}
		// usleep(200000);
		table = table->next;
	}

	join_threads(&table);
	expell_mutexes(&table);
	release_list(&table);
	return(0);
}
