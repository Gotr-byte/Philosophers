/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:29:17 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/31 17:08:50 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	weave_threads(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		if (last->nb % 2 == 0)
			usleep(50);
		pthread_create(&last->pt_id, NULL, living, last);
		last = last->next;
	}
	if (last->nb % 2 == 0)
		usleep(50);
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

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_mutex_init(&(last->fork), NULL);
		pthread_mutex_init(&(last->last_eaten_mutex), NULL);
		pthread_mutex_init(&(last->end), NULL);
		pthread_mutex_init(&(last->eaten_full_mutex), NULL);
		last = last->next;
	}
	pthread_mutex_init(&(last->last_eaten_mutex), NULL);
	pthread_mutex_init(&(last->fork), NULL);
	pthread_mutex_init(&(last->end), NULL);
	pthread_mutex_init(&(last->eaten_full_mutex), NULL);
}

void	expell_mutexes(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_mutex_destroy(&(last->fork));
		pthread_mutex_destroy(&(last->last_eaten_mutex));
		pthread_mutex_destroy(&last->end);
		pthread_mutex_destroy(&last->eaten_full_mutex);
		last = last->next;
	}
	pthread_mutex_destroy(&last->end);
	pthread_mutex_destroy(&(last->fork));
	pthread_mutex_destroy(&(last->last_eaten_mutex));
	pthread_mutex_destroy(&last->eaten_full_mutex);
}
