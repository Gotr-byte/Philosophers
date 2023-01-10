/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:49:46 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/10 14:41:24 by pbiederm         ###   ########.fr       */
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

// t_hourglass	*initialize_hourglass(t_hourglass *point_to_hourglass)
// {
// 	point_to_hourglass = NULL;
// 	point_to_hourglass = ft_calloc(1, sizeof(t_hourglass));
// 	return (point_to_hourglass);
// }

t_philosopher	*initialization_step(int ac, char **av, \
t_philosopher *table, t_timer *timer)
{
	long long unsigned int	i;

	i = 1;
	while (i <= ft_atoi_t(av[1]))
	{
		local_lstadd_back(&table, ft_lstnew_int(av, i, timer));
		i++;
	}
	if (ac == 6)
		set_eat_times(&table, ft_atoi_t(av[5]));
	last_point_first(&table);
	summon_mutexes(&table);
	return (table);
}
