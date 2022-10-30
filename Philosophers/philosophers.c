/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/30 16:15:39 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

//will need to replace calloc and atoi with ft_atoi
//libeartor function from so_long
//hard code for one philosopoher
//how to avoid deadlock
//manage delays of certain philosophers
// void	timestamp()
// the first one gets the fork (king of the table)

// pthread_mutex_t eatex;

const long int SECONDS_PER_DAY = 86400;

void *eating(void *arg)
{
	t_philosopher 	*philosopher;
	struct timeval 	start;
	
	philosopher = (t_philosopher *)arg;
	philosopher->time_to_die_curr = philosopher->time_to_die_set;
	// philosopher->sleep_time_curr = philosopher->sleep_time_set;
	while (TRUE)
	{
		if (philosopher->time_to_die_curr == 0)
		{
			gettimeofday(&start, NULL);
			printf("%ld %d has died\n", \
			(start.tv_sec * 1000 + start.tv_usec / 1000) - philosopher->zero_time,\
			philosopher->nb);
			pthread_exit(0);
		}
		else if(philosopher->nb == 1 && philosopher->sleep_time_curr == 0)
		{
			gettimeofday(&start, NULL);
			pthread_mutex_lock(&philosopher->next->fork);
			printf("%ld %d picked up a fork\n",\
			(start.tv_sec * 1000 + start.tv_usec / 1000) - philosopher->zero_time,\
			philosopher->nb);
			pthread_mutex_lock(&philosopher->fork);
			gettimeofday(&start, NULL);
			printf("%ld %d picked up a fork\n",\
			(start.tv_sec * 1000 + start.tv_usec / 1000) - philosopher->zero_time,\
			philosopher->nb);
			gettimeofday(&start, NULL);
			philosopher->sleep_time_curr = philosopher->sleep_time_set;
			printf("%ld %d is eating\n",\
			(start.tv_sec * 1000 + start.tv_usec / 1000) - philosopher->zero_time,\
			philosopher->nb);
			usleep(philosopher->gorge_time);
			pthread_mutex_unlock(&philosopher->fork);
			pthread_mutex_unlock(&philosopher->next->fork);
		}
		else if(philosopher->nb != 1 && philosopher->sleep_time_curr == 0)
		{
			pthread_mutex_lock(&philosopher->fork);
			gettimeofday(&start, NULL);
			printf("%ld %d picked up a fork\n",\
			(start.tv_sec * 1000 + start.tv_usec / 1000) - philosopher->zero_time,\
			philosopher->nb);
			pthread_mutex_lock(&philosopher->next->fork);
			gettimeofday(&start, NULL);
			printf("%ld %d picked up a fork\n",\
			(start.tv_sec * 1000 + start.tv_usec / 1000) - philosopher->zero_time,\
			philosopher->nb);
			gettimeofday(&start, NULL);
			philosopher->sleep_time_curr = philosopher->sleep_time_set;
			printf("%ld %d is eating\n",\
			(start.tv_sec * 1000 + start.tv_usec / 1000) - philosopher->zero_time,\
			philosopher->nb);
			usleep(philosopher->gorge_time);
			pthread_mutex_unlock(&philosopher->next->fork);
			pthread_mutex_unlock(&philosopher->fork);
		}
		else if (philosopher->sleep_time_curr > 0)
		{
			gettimeofday(&start, NULL);
			printf("%ld %d is sleeping\n", \
			(start.tv_sec * 1000 + start.tv_usec / 1000) - philosopher->zero_time,\
			philosopher->nb);
			usleep(philosopher->sleep_time_curr);
			philosopher->time_to_die_curr = philosopher->time_to_die_curr - philosopher->sleep_time_curr;
			philosopher->sleep_time_curr = 0;
			gettimeofday(&start, NULL);
			printf("%ld %d is taking his time thinking\n", \
			(start.tv_sec * 1000 + start.tv_usec / 1000) - philosopher->zero_time,\
			philosopher->nb);
		}
	
		// pthread_mutex_lock(&philosopher->next->fork);
		// printf("%ld %d picked up a fork\n",\
		// (start.tv_sec * 1000 + start.tv_usec / 1000),\
		// philosopher->nb);
		// pthread_mutex_lock(&philosopher->fork);
		// printf("%ld %d picked up a fork\n",\
		// (start.tv_sec * 1000 + start.tv_usec / 1000),\
		// philosopher->nb);
		// gettimeofday(&start, NULL);
		// usleep(philosopher->gorge_time);
		// philosopher->sleep_time_curr = philosopher->sleep_time_set;
		// gettimeofday(&end, NULL);
		// pthread_mutex_unlock(&philosopher->fork);
		// pthread_mutex_unlock(&philosopher->next->fork);
		// printf("%ld %d is eating\n",\
		// (start.tv_sec * 1000 + start.tv_usec / 1000),\
		// philosopher->nb);
	}
	return (NULL);
}

int main (int	ac, char **av)
{
	int				i;
	t_philosopher	*table;
	struct timeval	start;

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
	gettimeofday(&start, NULL);
	traverse_table(&table, (start.tv_sec * 1000 + start.tv_usec / 1000));
	summon_mutexes(&table);
	weave_threads(&table);
	join_threads(&table);
	expell_mutexes(&table);
	release_list(&table);
	return(0);
}
