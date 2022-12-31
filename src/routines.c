/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:37:16 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/31 18:51:03 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*living(void *arg)
{
	t_philosopher	*philosopher;
	int				has_eaten;

	has_eaten = 0;
	philosopher = (t_philosopher *)arg;
	while (TRUE)
	{
		eating(&philosopher);
		has_eaten++;
		printf("%d [has eaten]:[eat limit] | [%d]:[%d]\n", philosopher->nb, has_eaten, philosopher->eat_times);
		if (has_eaten == philosopher->eat_times && \
		philosopher->eat_times != -1)
			{
				pthread_mutex_lock(&philosopher->eaten_full_mutex);
				printf("%d has eaten full\n", philosopher->nb);
				philosopher->eaten_full_value = 1;
				pthread_mutex_unlock(&philosopher->eaten_full_mutex);
				pthread_exit(NULL);	
			}
		sleeping(&philosopher);
		thinking(&philosopher);
	}
	return (NULL);
}

int have_all_eaten(t_philosopher **table)
{
	t_philosopher	*checker;
	
	checker = *table;
	while (checker->indicator != LAST)
	{
		pthread_mutex_lock(&checker->eaten_full_mutex);
		if(checker->eaten_full_value == 0)
			return(0);
		pthread_mutex_unlock(&checker->eaten_full_mutex);
		checker = checker->next;
	}
	pthread_mutex_lock(&checker->eaten_full_mutex);
	if(checker->eaten_full_value == 0)
		return(0);
	pthread_mutex_unlock(&checker->eaten_full_mutex);
	return (1);
}

void	hourglass(t_philosopher **table, t_hourglass **hourglass_recieve)
{
	t_philosopher	*sands;
	t_hourglass		*point_to_hourglass;

	sands = *table;
	point_to_hourglass = *hourglass_recieve;
	while (TRUE)
	{
		while (sands->indicator != LAST)
		{
			pthread_mutex_lock(&sands->eaten_full_mutex);
			if (&sands->eaten_full_value)
			{
				printf("have all eaten %d", have_all_eaten(table));
				pthread_mutex_unlock(&sands->eaten_full_mutex);
				if (have_all_eaten(table))
				{
					// usleep(1000);
					return ;
				}
				continue;
			}
			pthread_mutex_unlock(&sands->eaten_full_mutex);
			pthread_mutex_lock(&sands->last_eaten_mutex);
			if (get_time() - sands->last_eaten >= sands->time_to_die_set)
			{
				pthread_mutex_lock(&sands->end);
				point_to_hourglass->end = END;
				printf("%ld %d has died\n", \
				get_time() - sands->hourglass_zero_time, \
				sands->nb);
				pthread_mutex_unlock(&sands->end);
				pthread_mutex_unlock(&sands->last_eaten_mutex);
				return ;
			}
			else
			{
				pthread_mutex_unlock(&sands->last_eaten_mutex);
				usleep (1000);
				sands = sands->next;	
			}
		}
		pthread_mutex_lock(&sands->last_eaten_mutex);
		if (get_time() - sands->last_eaten >= sands->time_to_die_set)
		{
			pthread_mutex_lock(&sands->end);
			point_to_hourglass->end = END;
			printf("%ld %d has died\n", \
			get_time() - sands->hourglass_zero_time, \
			sands->nb);
			pthread_mutex_unlock(&sands->end);
			pthread_mutex_unlock(&sands->last_eaten_mutex);
			return ;
		}
		else
		{
			pthread_mutex_unlock(&sands->last_eaten_mutex);
			usleep (1000);
			sands = sands->next;
		}
	}
}
			