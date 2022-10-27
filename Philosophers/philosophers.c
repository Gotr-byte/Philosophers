/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/27 16:57:55 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>




// pthread_mutex_t eatex;

void *eating(void *arg)
{
	t_philosopher 	*philosopher;
	struct timeval 	start, end;
	static int				i;

	philosopher = (t_philosopher *)arg;
	while (i < 3)
	{
		if (philosopher->sleep_time_curr > 0)
		{
			gettimeofday(&start, NULL);
			usleep(philosopher->sleep_time_curr);
			philosopher->sleep_time_curr = 0;
			gettimeofday(&end, NULL);
			printf("%ld %s is sleeping\n", \
			(start.tv_sec * 1000 + end.tv_usec / 1000),\
			(char *)philosopher->name);
		}
		else
		{
			gettimeofday(&start, NULL);
			printf("%ld %s is taking his time thinking\n", \
			(start.tv_sec * 1000 + end.tv_usec / 1000),\
			(char *)philosopher->name);
		}
		pthread_mutex_lock(&philosopher->next->fork);
		pthread_mutex_lock(&philosopher->fork);
		gettimeofday(&start, NULL);
		usleep(philosopher->gorge_time);
		philosopher->sleep_time_curr = philosopher->sleep_time_set;
		gettimeofday(&end, NULL);
		pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(&philosopher->next->fork);
		printf("%ld %s is eating\n",\
		(start.tv_sec * 1000 + end.tv_usec / 1000),\
		(char *)philosopher->name);
	
		i++;
	}

	return (arg);
}

int main (void)
{

	t_philosopher	*Konfucjusz = NULL;
	t_philosopher	*Marek = NULL;
	t_philosopher	*Platon = NULL;
	
	
	Platon = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	Konfucjusz = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	Marek = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	Konfucjusz->next = Platon;
	Platon->next = Marek;
	Marek->next = Konfucjusz;
	pthread_mutex_init(&(Konfucjusz->fork), NULL);
	pthread_mutex_init(&(Marek->fork), NULL);
	pthread_mutex_init(&(Platon->fork), NULL);
	Konfucjusz->name = (char *)calloc(11, sizeof(char));
	Marek->name = (char *)calloc(6, sizeof(char));
	Platon->name = (char *)calloc(7, sizeof(char));

	Konfucjusz->name = "Konfucjusz";
	Marek->name = "Marek";
	Platon->name = "Platon";

	Konfucjusz->gorge_time = 1000000;
	Marek->gorge_time = 1000000;
	Platon->gorge_time = 1000000;
	Konfucjusz->sleep_time_set = 2000000;
	Marek->sleep_time_set = 2000000;
	Platon->sleep_time_set = 2000000;

	pthread_create(&Konfucjusz->pt_id, NULL, eating, Konfucjusz);
	pthread_create(&Marek->pt_id, NULL, eating, Marek);
	pthread_create(&Platon->pt_id, NULL, eating, Platon);

	pthread_join(Konfucjusz->pt_id, NULL);
	pthread_join(Marek->pt_id, NULL);
	pthread_join(Platon->pt_id, NULL);
	pthread_mutex_destroy(&(Konfucjusz->fork));
	pthread_mutex_destroy(&(Marek->fork));
	pthread_mutex_destroy(&(Platon->fork));
	return (0);
}
