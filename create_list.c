/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:25:29 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/28 15:56:31 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

t_philosopher	*ft_lstnew_int(int content, int die, \
int eat, int sleep)
{
	t_philosopher	*tmp;
	// t_eatex			*fork;

	tmp = (t_philosopher *)ft_calloc(1, sizeof(t_philosopher));
	if (!tmp)
		return (NULL);
	if (!content)
		tmp->nb = 0;
	if (tmp)
	{
		tmp->nb = content;
		tmp->time_to_die_set = die;
		tmp->gorge_time = eat;
		tmp->sleep_time_set = sleep;
		tmp->eat_times = 0;
		// tmp->eatex = fork;
		tmp->next = NULL;

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
		printf("Number: %d\nIndicator: %d\nTime to die: %d\nTime to eat: %d\nTime to sleep: %d\nEat times: %d\nCurrent time: %ld\n",\
		last->nb, last->indicator, last->time_to_die_set, last->gorge_time, last->sleep_time_set, last->eat_times, last->zero_time);
		last = last->next;
	}
	last->zero_time = curr_time;
	last->last_eaten = curr_time;
	printf("Number: %d\nIndicator: %d\nTime to die: %d\nTime to eat: %d\nTime to sleep: %d\nEat times: %d\nCurrent time: %ld\n",\
	last->nb, last->indicator, last->time_to_die_set, last->gorge_time, last->sleep_time_set, last->eat_times, last->zero_time);
}
