/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:27:22 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/24 13:13:40 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// The POSIX standard header for using pthread library
#include <pthread.h>
// This function contains the logic which should be run as
// the body of a separate thread
void *thread_body(void *arg)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	char	*str = (char*)arg;
	printf("%s\n", str);
	gettimeofday(&end, NULL);
	printf("Time taken to run thread is: %ld micro seconds\n",\
	(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	usleep(500000);
	printf("Time taken to run thread is: %ld micro seconds\n",\
	(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	return (arg);
}

typedef struct	s_fruit
{
	pthread_t	p_fruit;
	char		*name;
}t_fruit;

int main (int argc, char **argv)
{
	//The thread handlers
	// pthread_t thread1;
	// pthread_t thread2;
	// pthread_t thread3;
	t_fruit	apple;
	t_fruit	orange;
	t_fruit lemon;

	apple.name = (char *)calloc(6, sizeof(char));
	orange.name = (char *)calloc(7, sizeof(char));
	lemon.name = (char *)calloc(6, sizeof(char));

	apple.name = "Apple";
	orange.name = "Orange";
	lemon.name = "Lemon";

	// Create new threads
	int result1 = pthread_create(&apple.p_fruit, NULL, thread_body, apple.name);
	int result2 = pthread_create(&orange.p_fruit, NULL, thread_body, orange.name);
	int result3 = pthread_create(&lemon.p_fruit, NULL, thread_body, lemon.name);
	
	// If the thread creation did not succeed
	if (result1 || result2 || result3)
	{
		printf("The threads could not be created.\n");
		exit(1);
	}
	// Detach the thread
	// result = pthread_detach(thread);
	// If detaching the thread did not succeed

	result1 = pthread_join(apple.p_fruit, NULL);
	result2 = pthread_join(orange.p_fruit, NULL);
	result3 = pthread_join(lemon.p_fruit, NULL);
	// If joining the thread did not succed
	if (result1 || result2 || result3)
	{
		printf("The threads could not be joined.\n");
		exit (2);
	}
	// pthread_exit(NULL);
	return (0);
}


// #include <sys/time.h>
// #include <stdio.h>

// int	main()
// {
// 	struct timeval start, end;
// 	gettimeofday(&start, NULL);

// 	for (int i = 0; i < 1e5; i++)
// 	{
// 		gettimeofday(&end, NULL);
// 		printf("Time taken to count to 10ˆ5 is: %ld micro seconds\n"),\
// 		((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
// 	}
// }