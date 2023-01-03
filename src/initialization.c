/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:49:46 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/03 20:36:42 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	return (table);
}
