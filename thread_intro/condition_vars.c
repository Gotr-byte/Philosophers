/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:26:05 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/21 17:02:33 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

pthread_mutex_t mutex_fuel;
pthread_cond_t	condFuel;
int fuel = 0;

	void	*fuel_filling(void	*arg)
	{
		for (int i = 0; i < 5; i++)
		{
			pthread_mutex_lock(&mutex_fuel);
			fuel += 60;
			printf("Filled fuel... %d\n", fuel);
			pthread_mutex_unlock(&mutex_fuel);
			pthread_cond_signal(&condFuel);
			sleep(1);
		}
	}

	void *car(void	*arg)
	{
		pthread_mutex_lock(&mutex_fuel);
		while (fuel < 40)
		{
			printf("No fuel. Waiting...\n");
			pthread_cond_wait(&condFuel, &mutex_fuel);
		}
		fuel -= 40;
		printf("Got fuel. Now left: %d\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
	}

int	main(int argc, char *argv[])
{
	pthread_t th[5];
	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_cond_init(&condFuel, NULL);
	for (int i = 0; i < 5; i++)
	{
		if (i == 4)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
			{
				perror("Failed to create thread");
			}
		}
		else
		{
			if(pthread_create(&th[i], NULL, &car, NULL) != 0)
			{
				perror("Failed to create thread");
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if(pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
		}
	}
	pthread_mutex_destroy(&mutex_fuel);
	pthread_cond_destroy(&condFuel);
	return (0);
}