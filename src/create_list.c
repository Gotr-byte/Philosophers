/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:25:29 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/08 18:29:14 by pbiederm         ###   ########.fr       */
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

t_philosopher	*ft_lstnew_int(char **av, int content, t_timer *timer)
{
	t_philosopher	*tmp;

	tmp = (t_philosopher *)ft_calloc(1, sizeof(t_philosopher));
	if (!tmp)
		return (NULL);
	if (!content)
		tmp->nb = 0;
	if (tmp)
	{
		tmp->nb = content;
		tmp->end = NOT_END;
		tmp->number_of_philosophers = ft_atoi_t(av[1]);
		tmp->time_to_die_set = ft_atoi_t(av[2]);
		tmp->gorge_time = ft_atoi_t(av[3]);
		tmp->sleep_time_set = ft_atoi_t(av[4]);
		tmp->eat_times = -1;
		tmp->eaten_full_value = NOT_EATEN_FULL;
		tmp->next = NULL;
		tmp->timer = timer;
	}
	return (tmp);
}
