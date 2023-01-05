/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:29:17 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/05 17:58:00 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	get_values(t_philosopher **lst)
{
	t_philosopher *last;
	long			start_time;
	
	last = *lst;
	start_time = get_time() + 5000;
	while (last->indicator != LAST)
	{
		last->zero_time = start_time;
		last->hourglass_zero_time = start_time;
		last->hourglass->hourglass_zero_time = start_time;
		last->last_eaten = start_time;
		last->start = 0;
		last->hourglass->start = 0;
		last = last->next;
	}
	last->zero_time = start_time;
	last->hourglass_zero_time = start_time;
	last->hourglass->hourglass_zero_time = start_time;
	last->last_eaten = start_time;
	last->start = 0;
	last->hourglass->start = 0;
}

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

	last = *lst;
	pthread_mutex_init(&(last->hourglass->print_guard_mutex), NULL);
	while (last->indicator != LAST)
	{
		pthread_mutex_init(&(last->fork), NULL);
		pthread_mutex_init(&(last->last_eaten_mutex), NULL);
		pthread_mutex_init(&(last->end_mutex), NULL);
		last = last->next;
	}
	pthread_mutex_init(&(last->last_eaten_mutex), NULL);
	pthread_mutex_init(&(last->fork), NULL);
	pthread_mutex_init(&(last->end_mutex), NULL);
}

void	expell_mutexes(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	pthread_mutex_destroy(&(last->hourglass->print_guard_mutex));
	while (last->indicator != LAST)
	{
		pthread_mutex_destroy(&(last->fork));
		pthread_mutex_destroy(&(last->last_eaten_mutex));
		pthread_mutex_destroy(&last->end_mutex);
		last = last->next;
	}
	pthread_mutex_destroy(&last->end_mutex);
	pthread_mutex_destroy(&(last->fork));
	pthread_mutex_destroy(&(last->last_eaten_mutex));
}
