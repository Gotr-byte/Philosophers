/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:37:16 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/31 16:41:50 by pbiederm         ###   ########.fr       */
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
		if (has_eaten == philosopher->eat_times && \
		philosopher->eat_times != -1)
			pthread_exit(NULL);
		sleeping(&philosopher);
		thinking(&philosopher);
	}
	return (NULL);
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
			