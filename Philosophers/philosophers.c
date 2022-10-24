/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/24 13:49:44 by pbiederm         ###   ########.fr       */
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
}t_philosopher;

void *living(void *arg)
{
	t_philosopher *philosopher;
	struct timeval start, end;

	philosopher = (t_philosopher *)arg;
	gettimeofday(&start, NULL);
	usleep(philosopher->gorge_time);
	gettimeofday(&end, NULL);
	printf("Actual time taken to for %s to eat is: %ld micro seconds\nSet time is: %d\n",\
	(char *)philosopher->name,\
	(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec),\
	philosopher->gorge_time);
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

	int result1 = pthread_create(&Konfucjusz->pt_id, NULL, living, Konfucjusz);
	int result2 = pthread_create(&Marek->pt_id, NULL, living, Marek);
	int result3 = pthread_create(&Platon->pt_id, NULL, living, Platon);
	
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
	// pthread_exit(NULL);
	return (0);
}



// void *living(void	*index)
// {
// 	int	eat_counter;
// 	int	think_counter;
// 	int	j;

// 	printf("index value %d\n", *((int*)index));
// 	think_counter = 0;
// 	j = *((int*)index);
// 	printf("j value equals: %d\n", *(int*)index);
// 	eat_counter = 0;
// 	if ((*((int*)index) == 0))
// 	{
// 	while (eat_counter < 5)
// 	{
// 		printf ("Philosopher %d is eating\n", j);
// 		usleep(200000);
// 		eat_counter++;
// 	}
// 	}
// 	if ((*((int*)index) == 1))
// 	{
// 		printf("Philosopher %d is thinking\n", j);
// 		usleep(500000);
// 		think_counter++;
// 	}
// 	if ((*((int*)index) == 2))
// 	{
// 		printf("Philosopher %d is sleeping\n", j);
// 		usleep(500000);
// 		think_counter++;
// 	}
// 	return(NULL);
// }


// // void *thinking(void		*index)
// // {
// // 	int	think_counter;
// // 	int	j;

// // 	j = *((int*)index);
// // 	think_counter = 0;
// // 	while (think_counter < 10)
// // 	{
// // 		printf("Philosopher %d is thinking\n", j);
// // 		usleep(500000);
// // 		think_counter++;
// // 	}
// // }

// // void	*sleeping()
// // {
// // 	printf("Philosopher is sleeping\n");
// // }

// int main()
// {
// 	pthread_t	philosopher;
// 	int			i;

// 	i = 0;
// 	while (i < 3)
// 	{
// 		pthread_create(&philosopher, NULL, &living, (void*)&i);
// 		i++;
// 	}
// 	pthread_join(philosopher, NULL);
// }