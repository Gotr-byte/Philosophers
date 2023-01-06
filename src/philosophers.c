/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/06 19:13:19 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


void point_to_reaper(t_philosopher **table, t_timer *reaper)
{
	t_philosopher *traverse;
	int traverse_times;

	traverse = *table;
	traverse_times = traverse->number_of_philosophers;
	while (traverse_times >= 0)
	{
		traverse->timer = reaper;
		traverse_times--;
	}
}

/*Needs a function that checks if any are alive. May make a lite version.
Needs a way to traverse all of the elements of an array. Maybe add a value
to the hourglass struct.*/
int	main(int ac, char **av)
{
	t_philosopher	*table;
	t_hourglass		*point_to_hourglass;
	t_timer			*reaper;

	table = NULL;
	point_to_hourglass = NULL;
	reaper = NULL;
	if (argument_number_check(ac, av) != 0)
		return (2);
	if (single_philosopher(av))
		return (0);
	reaper = malloc(sizeof(reaper));
	reaper->id = 0;
	point_to_hourglass = initialize_hourglass(point_to_hourglass);
	table = initialization_step(ac, av, table, point_to_hourglass);
	reaper->philosophers = table;
	reaper->hourglass = point_to_hourglass;
	reaper->number_of_full_philosophers_in_timer = 0;
	pthread_mutex_init(&reaper->full_philosophers_mutex_in_timer, NULL);
	weave_threads(&table);
	pthread_create(&reaper->id, NULL, hourglass, reaper);
	pthread_join(reaper->id, NULL);
	join_threads(&table);
	expell_mutexes(&table);
	pthread_mutex_destroy(&reaper->full_philosophers_mutex_in_timer);
	release_list(&table, point_to_hourglass, reaper);
	return (0);
}
