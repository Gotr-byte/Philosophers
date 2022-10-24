/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:48:41 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/22 20:09:45 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread funcion to generate sum of 0 to N
void *sum_runner(void	*arg)
{
	long long *limit_ptr = (long long *)arg;
	long long limit = *limit_ptr;
	//The sum computed by the background thread
	long long sum = 0;
	for (long long i = 0; i <= limit; i++)
	{
		sum += i;
	}
	// What to do with the answer?
	// sum is a global variable, so other threads can access
	printf("Sum is %lld\n", sum);
	pthread_exit(0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage: %s <num>\n", argv[0]);
		exit(-1);
	}
	long long limit = atoll(argv[1]);
	//Thread Id
	pthread_t tid;

	// Create attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid, &attr, sum_runner, &limit);
	// Do other stuff here
	// Wait untill thread is done its work
	pthread_join(tid, NULL);
	

}