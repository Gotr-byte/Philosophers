/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/24 19:32:31 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./philosophers.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

typedef struct	s_philo
{
	pthread_t	pt_id;
	char		*name;
	int			gorge_time;
	int			sleep_time;
	int			think_time;
	int			time_to_die;
	//mutex to point to something
}t_philosopher;

void *eating(void *arg)
{
	t_philosopher 	*philosopher;
	struct timeval 	start, end;
	static struct timeval current;
	static int				i;

	while (i < 3)
	{
		philosopher = (t_philosopher *)arg;
		gettimeofday(&start, NULL);
		usleep(philosopher->gorge_time);
		gettimeofday(&end, NULL);
		printf("Current time is: %ld\nActual time taken to for %s to eat is: %ld micro seconds\nSet time is: %d\n",\
		(current.tv_sec * 1000000 + current.tv_usec),\
		(char *)philosopher->name,\
		(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec),\
		philosopher->gorge_time);
		i++;
	}

	return (arg);
}

void *sleeping(void *arg)
{
	t_philosopher 	*philosopher;
	struct timeval 	start, end;
	static struct timeval current;
	static int				i;

	while (i < 2)
	{
		philosopher = (t_philosopher *)arg;
		gettimeofday(&start, NULL);
		usleep(philosopher->sleep_time);
		gettimeofday(&end, NULL);
		printf("Current time is: %ld\nActual time taken to for %s to sleep is: %ld micro seconds\nSet time is: %d\n",\
		(current.tv_sec * 1000000 + current.tv_usec),\
		(char *)philosopher->name,\
		(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec),\
		philosopher->sleep_time);
		i++;
	}

	return (arg);
}


int main (void)
{
	t_philosopher	*Konfucjusz = NULL;
	t_philosopher	*Marek = NULL;
	t_philosopher	*Platon = NULL;

	Konfucjusz = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	Marek = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	Platon = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	Konfucjusz->name = (char *)calloc(11, sizeof(char));
	Marek->name = (char *)calloc(6, sizeof(char));
	Platon->name = (char *)calloc(7, sizeof(char));

	Konfucjusz->name = "Konfucjusz";
	Marek->name = "Marek";
	Platon->name = "Platon";

	Konfucjusz->gorge_time = 100000;
	Marek->gorge_time = 50000;
	Platon->gorge_time = 77000;
	Marek->sleep_time = 40000;

	int result1 = pthread_create(&Konfucjusz->pt_id, NULL, eating, Konfucjusz);
	int result2 = pthread_create(&Marek->pt_id, NULL, sleeping, Marek);
	int result3 = pthread_create(&Platon->pt_id, NULL, eating, Platon);
	
	if (result1 || result2 || result3)
	{
		printf("The threads could not be created.\n");
		exit(1);
	}

	result1 = pthread_join(Konfucjusz->pt_id, NULL);
	result2 = pthread_join(Marek->pt_id, NULL);
	result3 = pthread_join(Platon->pt_id, NULL);

	if (result1 || result2 || result3)
	{
		printf("The threads could not be joined.\n");
		exit (2);
	}
	return (0);
}
