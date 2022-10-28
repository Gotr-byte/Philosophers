/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barriers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:29:41 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/21 20:37:05 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

ptread_barrier_t barrier;

void	*routine(void	*args)
{
	printf("Waiting at the barrier...\n");
	pthread_barrier_wait(&barrier);
	printf("We passed the barrier\n");
}

int	main(int argc, char	*argv[])
{
	pthread_t th[2];
	int i;
	pthread_barrier_init(&barrier, NULL, 3);
	for (i = 0; i < 2; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
		}
	}
	for (i = 0; i < 2; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread \n");
		}
	}
	pthread_barrier_destroy(&barrier);
	return(0);
}