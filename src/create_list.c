/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:25:29 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/01 15:57:30 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	last_point_first(t_philosopher **lst)
{
	t_philosopher	*last;
	t_philosopher	*first;

	last = *lst;
	while (last)
	{
		if (last->next == NULL)
			break ;
		last->indicator = NOT_LAST;
		last = last->next;
	}
	last->indicator = LAST;
	first = *lst;
	last->next = first;
	return ;
}

void	local_lstadd_back(t_philosopher **lst, t_philosopher *new)
{
	t_philosopher	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last)
	{
		if (last->next == NULL)
			break ;
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
	return ;
}

t_philosopher	*ft_lstnew_int(int number_of_philo, int content, int die, \
int eat, int sleep, t_hourglass **hourglass_recieve)
{
	t_philosopher	*tmp;
	t_hourglass		*point_to_hourglass;

	point_to_hourglass = *hourglass_recieve;
	tmp = (t_philosopher *)ft_calloc(1, sizeof(t_philosopher));
	if (!tmp)
		return (NULL);
	if (!content)
		tmp->nb = 0;
	if (tmp)
	{
		tmp->nb = content;
		tmp->number_of_philosophers = number_of_philo;
		tmp->time_to_die_set = die;
		tmp->gorge_time = eat;
		tmp->sleep_time_set = sleep;
		tmp->eat_times = -1;
		tmp->eaten_full_value = NOT_EATEN_FULL;
		tmp->next = NULL;
		tmp->hourglass = point_to_hourglass;
	}
	return (tmp);
}

void	traverse_table(t_philosopher **lst, long curr_time)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		last->zero_time = curr_time;
		last->hourglass_zero_time = curr_time;
		last->last_eaten = curr_time;
		printf("Number: %d\nIndicator: %d\nTime to die: %d\nTime to eat: %d\nTime to sleep: %d\nEat times: %d\nCurrent time: %ld\n Eatean_full_value %d\n",\
		last->nb, last->indicator, last->time_to_die_set, last->gorge_time, last->sleep_time_set, last->eat_times, last->zero_time, last->eaten_full_value);
		last = last->next;
	}
	last->zero_time = curr_time;
	last->hourglass_zero_time = curr_time;
	last->last_eaten = curr_time;
	printf("Number: %d\nIndicator: %d\nTime to die: %d\nTime to eat: %d\nTime to sleep: %d\nEat times: %d\nCurrent time: %ld\n",\
	last->nb, last->indicator, last->time_to_die_set, last->gorge_time, last->sleep_time_set, last->eat_times, last->zero_time);
}
