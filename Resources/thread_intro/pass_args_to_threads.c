/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_args_to_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:27:40 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/20 10:55:03 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 17, 19, 23, 29 };

void *routine(void * arg)
{
	sleep(1);
	int index = *(int *)arg;
	printf("Printing primes val %d\n", primes[index]);
	free(arg);
}

int main(int argc, char	*argv[])
{
	pthread_t th[10];
	int i;
	
	for (i = 0; i < 10; i++)
	{
		int	*a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			
			perror("Failed to create thread\n");
		}
	}
	for (i = 0; i < 10; i++)
	{
		if(pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
		}
	}
	return (0);
}