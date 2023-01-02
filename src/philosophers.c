/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/02 17:47:34 by pbiederm         ###   ########.fr       */
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
		pthread_mutex_lock(&philosopher_doing->end_mutex);
		if (philosopher_doing->hourglass->end == END)
		{
			pthread_mutex_unlock(&philosopher_doing->end_mutex);
			pthread_mutex_unlock(&philosopher_doing->next->fork);
			pthread_mutex_unlock(&philosopher_doing->fork);
			pthread_exit(NULL);
		}
		else
		{
			pthread_mutex_unlock(&philosopher_doing->end_mutex);
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
		pthread_mutex_lock(&philosopher_doing->end_mutex);
		if (philosopher_doing->hourglass->end == END)
		{
			pthread_mutex_unlock(&philosopher_doing->end_mutex);
			pthread_exit(NULL);
		}
		else
		{
			pthread_mutex_unlock(&philosopher_doing->end_mutex);
			usleep(100);
		}
	}
}

void	print_safeguard(t_philosopher **philosopher_struct)
{
	t_philosopher	*philosopher_local;

	philosopher_local = *philosopher_struct;
	pthread_mutex_lock(&philosopher_local->end_mutex);
	if (philosopher_local->hourglass->end == END)
	{
		pthread_mutex_unlock(&philosopher_local->fork);
		pthread_mutex_unlock(&philosopher_local->end_mutex);
		pthread_exit(NULL);
	}
	else
		pthread_mutex_unlock(&philosopher_local->end_mutex);
}

void	set_eat_times(t_philosopher **table, int eat_number)
{
	t_philosopher	*eat_goal;

	eat_goal = *table;
	while (eat_goal)
	{
		eat_goal->eat_times = eat_number;
		eat_goal = eat_goal->next;
	}
}


t_hourglass	*initialize_hourglass(t_hourglass *point_to_hourglass)
{

	point_to_hourglass = NULL;
	point_to_hourglass = ft_calloc(1, sizeof(t_hourglass));
	point_to_hourglass->end = NOT_END;
	point_to_hourglass->number_of_full_philosophers = 0;
	return (point_to_hourglass);
}

t_philosopher	*initialization_step(int ac, char **av, \
t_philosopher *table, t_hourglass *point_to_hourglass)
{
	long long unsigned int	i;

	i = 1;
	while (i <= ft_atoi_t(av[1]))
	{
		local_lstadd_back(&table, ft_lstnew_int(av, i, &point_to_hourglass));
		i++;
	}
	if (ac == 6)
		set_eat_times(&table, ft_atoi_t(av[5]));
	last_point_first(&table);
	traverse_table(&table, get_time());
	summon_mutexes(&table);
	return(table);
}


int	main(int ac, char **av)
{
	// unsigned int	i;
	t_philosopher	*table;
	t_hourglass		*point_to_hourglass;

	table = NULL;
	point_to_hourglass = NULL;
	if (argument_number_check(ac, av) != 0)
		return (2);
	if (single_philosopher(av))
		return (0);
	point_to_hourglass = initialize_hourglass(point_to_hourglass);
	table = initialization_step(ac, av, table, point_to_hourglass);
	// initialize_hourglass(&point_to_hourglass);
	// i = 1;
	// while (i <= ft_atoi_t(av[1]))
	// {
	// 	local_lstadd_back(&table, ft_lstnew_int(av, i, &point_to_hourglass));
	// 	i++;
	// }
	// if (ac == 6)
	// 	set_eat_times(&table, ft_atoi_t(av[5]));
	// last_point_first(&table);
	// traverse_table(&table, get_time());
	// summon_mutexes(&table);
	weave_threads(&table);
	// printf ("seg check\n");
	// exit (0);	
	hourglass(&table, &point_to_hourglass);
	join_threads(&table);
	expell_mutexes(&table);
	release_list(&table, point_to_hourglass);
	return (0);
}
