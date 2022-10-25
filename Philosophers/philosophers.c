/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/25 12:43:06 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./philosophers.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_eatex
{
	pthread_mutex_t eatex;
}t_eatex;


typedef struct s_time
{
	long			*curr_time;
}t_time;

typedef struct	s_philo
{
	pthread_t	pt_id;
	char		*name;
	int			gorge_time;
	int			sleep_time;
	int			think_time;
	int			time_to_die;
	t_time		*ptr;
	t_eatex		*ptr_m;
	//mutex to point to something
}t_philosopher;


void *eating(void *arg)
{
	t_philosopher 	*philosopher;
	struct timeval 	start, end;
	static int				i;

	while (i < 3)
	{
		philosopher = (t_philosopher *)arg;
		gettimeofday(&start, NULL);
		usleep(philosopher->gorge_time);
		gettimeofday(&end, NULL);
		pthread_mutex_lock(&philosopher->ptr_m->eatex);
		*(philosopher->ptr->curr_time) = *(philosopher->ptr->curr_time) + ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		printf("Current time is: %ld\nActual time taken to for %s to eat is: %ld micro seconds\nSet time is: %d\n",\
		*(philosopher->ptr->curr_time) ,\
		(char *)philosopher->name,\
		(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec),\
		philosopher->gorge_time);
		i++;
		pthread_mutex_unlock(&philosopher->ptr_m->eatex);
	}

	return (arg);
}

void *sleeping(void *arg)
{
	t_philosopher 	*philosopher;
	struct timeval 	start, end;
	static int				i;

	while (i < 2)
	{
		philosopher = (t_philosopher *)arg;
		gettimeofday(&start, NULL);
		usleep(philosopher->sleep_time);
		gettimeofday(&end, NULL);
		*(philosopher->ptr->curr_time) = *(philosopher->ptr->curr_time) + ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		printf("Current time is: %ld\nActual time taken to for %s to sleep is: %ld micro seconds\nSet time is: %d\n",\
		*(philosopher->ptr->curr_time) ,\
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
	t_time			*init;
	t_eatex			*init_m;

	init = (t_time *)calloc (2, sizeof(t_time));
	init_m = (t_eatex *)calloc(2, sizeof(t_eatex));
	pthread_mutex_init(&init_m->eatex, NULL);
	Konfucjusz->ptr_m = init_m;
	Marek->ptr_m = init_m;
	Platon->ptr_m = init_m;
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

	*(init->curr_time) = 0;
	// *(Konfucjusz->ptr->curr_time) = 0;
	// *(Marek->ptr->curr_time = 0);
	// *(Platon->ptr->curr_time = 0);

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
	pthread_mutex_destroy(&init_m->eatex);
	if (result1 || result2 || result3)
	{
		printf("The threads could not be joined.\n");
		exit (2);
	}
	return (0);
}
