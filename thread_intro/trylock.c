/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trylock.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:26:11 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/20 17:24:27 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex;

void	*routine(void *arg)
{
	if (pthread_mutex_trylock(&mutex) == 0)
	{
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
	else
	{
		printf("Didn't get lock \n");
	}
}

int main(int argc, char	*argv[])
{
	pthread_t	th[4];
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++)
	{
		if(pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Error at creating thread\n");
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if(pthread_join(th[i], NULL) != 0)
		{
			perror("Error at joining thread\n");
		}
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
