/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/31 16:49:42 by pbiederm         ###   ########.fr       */
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
			printf("This is the end of thread %d\n", philosopher_doing->nb);
			pthread_mutex_unlock(&philosopher_doing->end);
			pthread_mutex_unlock(&philosopher_doing->next->fork);
			pthread_mutex_unlock(&philosopher_doing->fork);
			pthread_exit(NULL);
		}
		else
		{
			pthread_mutex_unlock(&philosopher_doing->end);
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
		pthread_mutex_lock(&philosopher_doing->end);
		if (philosopher_doing->hourglass->end == END)
		{
			printf("This is the end of thread %d\n", philosopher_doing->nb);
			pthread_mutex_unlock(&philosopher_doing->end);
			pthread_exit(NULL);
		}
		else
		{
			pthread_mutex_unlock(&philosopher_doing->end);
			usleep(100);
		}
	}
}
			

void	print_safeguard(t_philosopher **philosopher_struct)
{
	t_philosopher	*philosopher_local;

	philosopher_local = *philosopher_struct;
	pthread_mutex_lock(&philosopher_local->end);
	if (philosopher_local->hourglass->end == END)
	{
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

int	main(int ac, char **av)
{
	unsigned int	i;
	t_philosopher	*table;
	t_hourglass		*point_to_hourglass;

	if (argument_number_check(ac, av) != 0)
		return (2);
	table = NULL;
	point_to_hourglass = NULL;
	point_to_hourglass = ft_calloc(1, sizeof(t_hourglass));
	point_to_hourglass->end = NOT_END;
	i = 1;
	if (ft_atoi_t(av[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi_t(av[2]) * 1000);
		printf("%lld 1 has died\n", ft_atoi_t(av[2]));
		return (0);
	}
	while (i <= ft_atoi_t(av[1]))
	{
		local_lstadd_back(&table, ft_lstnew_int(i, ft_atoi_t(av[2]), \
		ft_atoi_t(av[3]), ft_atoi_t(av[4]), &point_to_hourglass));
		i++;
	}
	if (ac == 6)
	{
		table->eat_times = ft_atoi_t(av[5]);
	}
	last_point_first(&table);
	traverse_table(&table, get_time());
	summon_mutexes(&table);
	weave_threads(&table);
	hourglass(&table, &point_to_hourglass);
	join_threads(&table);
	expell_mutexes(&table);
	release_list(&table, point_to_hourglass);
	return (0);
}
