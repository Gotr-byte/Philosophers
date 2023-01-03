/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/03 20:48:34 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Needs a function to check if everyone has eaten.
*/
#include "../includes/philosophers.h"


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
