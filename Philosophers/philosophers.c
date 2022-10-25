/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/25 18:14:31 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>




pthread_mutex_t eatex;
// pthread_muted_t sleepex;


void *eating(void *arg)
{
	t_philosopher 	*philosopher;
	struct timeval 	start, end;
	static int				i;

	while (i < 3)
	{
		philosopher = (t_philosopher *)arg;
		if (philosopher->sleep_time_curr > 0)
		{
			gettimeofday(&start, NULL);
			usleep(philosopher->sleep_time_curr);
			philosopher->sleep_time_curr = 0;
			gettimeofday(&end, NULL);
			printf("Current time is: %ld\nActual time taken to for %s to sleep is: %ld micro seconds\nSet time is: %d\n", \
			(start.tv_sec * 1000000 + end.tv_usec),\
			(char *)philosopher->name,\
			(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec),\
			philosopher->sleep_time_set);
		}
		else
		{
			gettimeofday(&start, NULL);
			printf("Current time is: %ld\n %s is taking his time thinking\n", \
			(start.tv_sec * 1000000 + end.tv_usec),\
			(char *)philosopher->name);
		}
		pthread_mutex_lock(&eatex);
		gettimeofday(&start, NULL);
		usleep(philosopher->gorge_time);
		philosopher->sleep_time_curr = philosopher->sleep_time_set;
		gettimeofday(&end, NULL);
		printf("Current time is: %ld\nActual time taken to for %s to eat is: %ld micro seconds\nSet time is: %d\n",\
		(start.tv_sec * 1000000 + end.tv_usec),\
		(char *)philosopher->name,\
		(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec),\
		philosopher->gorge_time);
		pthread_mutex_unlock(&eatex);
		i++;
	}

	return (arg);
}

int main (void)
{
	t_philosopher	*Konfucjusz = NULL;
	t_philosopher	*Marek = NULL;
	t_philosopher	*Platon = NULL;

	pthread_mutex_init(&eatex, NULL);
	// pthread_mutex_init(&sleepex, NULL);
	Konfucjusz = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	Marek = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	Platon = (t_philosopher*)calloc(1, sizeof(t_philosopher));
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

	int result1 = pthread_create(&Konfucjusz->pt_id, NULL, eating, Konfucjusz);
	int result2 = pthread_create(&Marek->pt_id, NULL, eating, Marek);
	int result3 = pthread_create(&Platon->pt_id, NULL, eating, Platon);
	
	if (result1 || result2 || result3)
	{
		printf("The threads could not be created.\n");
		exit(1);
	}

	result1 = pthread_join(Konfucjusz->pt_id, NULL);
	result2 = pthread_join(Marek->pt_id, NULL);
	result3 = pthread_join(Platon->pt_id, NULL);
	pthread_mutex_destroy(&eatex);
	// pthread_mutex_destroy(&sleepex);
	if (result1 || result2 || result3)
	{
		printf("The threads could not be joined.\n");
		exit (2);
	}
	return (0);
}
