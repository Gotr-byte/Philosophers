/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   race_cond.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:23:36 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/20 09:06:16 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 1000000; i++)
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// read mail
		// increment
		// write mails
}

int	main(int argc, char	*argv[])
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL))
	{
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine, NULL))
	{
		return (2);
	}
	if (pthread_join(t1, NULL))
	{
		return (3);
	}
	if (pthread_join(t2, NULL))
	{
		return (4);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d", mails);
	return (0);
}
