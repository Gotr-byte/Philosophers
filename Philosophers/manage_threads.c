/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:29:17 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/31 19:15:56 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	weave_threads(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		if(last->nb % 2 == 0)
			usleep(200000);
		pthread_create(&last->pt_id, NULL, eating, last);
		last = last->next;
	}
	pthread_create(&last->pt_id, NULL, eating, last);
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

void	summon_mutexes(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_mutex_init(&(last->fork), NULL);
		last = last->next;
	}
	pthread_mutex_init(&(last->fork), NULL);
}

void	expell_mutexes(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_mutex_destroy(&(last->fork));
		last = last->next;
	}
	pthread_mutex_destroy(&(last->fork));
}
