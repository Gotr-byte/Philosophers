/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/10 15:02:40 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	reaper_init(t_timer *reaper, t_philosopher *table)
{
	reaper->id = 0;
	reaper->philosophers = table;
	reaper->number_of_philosophers_in_timer = table->number_of_philosophers;
}

int	main(int ac, char **av)
{
	t_philosopher	*table;
	t_timer			*reaper;

	table = NULL;
	reaper = NULL;
	if (argument_number_check(ac, av) != 0)
		return (2);
	if (single_philosopher(av))
		return (0);
	reaper = ft_calloc(8, sizeof(reaper));
	table = initialization_step(ac, av, table, reaper);
	reaper->time_to_die = ft_atoi_t(av[2]);
	reaper_init(reaper, table);
	weave_threads(&table);
	pthread_create(&reaper->id, NULL, hourglass, reaper);
	pthread_join(reaper->id, NULL);
	join_threads(&table);
	expell_mutexes(&table);
	release_list(&table, reaper);
	return (0);
}
