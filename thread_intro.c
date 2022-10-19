/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_intro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:13:50 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/13 13:52:53 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>

void* myturn(void * arg)
{
	int *iptr = (int *)malloc(sizeof(int));
	*iptr = 5;
	for(int i = 0; i < 8; i++)
	{
		sleep(1);
		printf("My Turn %d %d\n", i, *iptr);
		(*iptr)++;
	}
	return iptr;
}

void yourturn()
{
	for(int i = 0; i < 3; i++)
	{
		sleep(2);
		printf("Your Turn\n");
	}
}

int main()
{
	pthread_t newthread;
	int			*result;

	pthread_create(&newthread, NULL, myturn, NULL);
	yourturn();
	pthread_join(newthread, (void*)&result);
	printf("thread's done: v=%d\n", *result);
}
