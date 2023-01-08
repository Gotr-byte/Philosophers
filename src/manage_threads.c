/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:29:17 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/08 16:27:33 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	weave_threads(t_philosopher **lst)
{
	t_philosopher	*last;

	get_values(lst);
	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_create(&last->pt_id, NULL, living, last);
		last = last->next;
	}
	pthread_create(&last->pt_id, NULL, living, last);
}

void	join_threads(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_join(last->pt_id, NULL);
		last = last->next;
	}
	pthread_join(last->pt_id, NULL);
}

void	detach_threads(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_detach(last->pt_id);
		last = last->next;
	}
	pthread_detach(last->pt_id);
}

void	summon_mutexes(t_philosopher **lst)
{
	t_philosopher	*last;
	int				traverse;

	last = *lst;
	traverse = last->number_of_philosophers;
	while (traverse > 0)
	{
		pthread_mutex_init(&(last->fork), NULL);
		pthread_mutex_init(&(last->last_eaten_mutex), NULL);
		pthread_mutex_init(&(last->end_mutex), NULL);
		last = last->next;
		traverse--;
	}
}

void	expell_mutexes(t_philosopher **lst)
{
	t_philosopher	*last;
	int				traverse;

	last = *lst;
	traverse = last->number_of_philosophers;
	while (traverse > 0)
	{
		pthread_mutex_destroy(&(last->fork));
		pthread_mutex_destroy(&(last->last_eaten_mutex));
		pthread_mutex_destroy(&last->end_mutex);
		last = last->next;
		traverse--;
	}
}
