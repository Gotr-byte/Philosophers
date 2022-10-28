/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:06:22 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/13 19:22:14 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Errors might be due to mac 

// 16_4.c:18:1: error: unknown type name 'pthread_barrier_t'
// pthread_barrier_t barrier;
// ^
// 16_4.c:23:2: error: implicit declaration of function 'pthread_barrier_wait' is invalid in C99
//       [-Werror,-Wimplicit-function-declaration]
//         pthread_barrier_wait(&barrier);
//         ^
// 16_4.c:30:2: error: implicit declaration of function 'pthread_barrier_wait' is invalid in C99
//       [-Werror,-Wimplicit-function-declaration]
//         pthread_barrier_wait(&barrier);
//         ^
// 16_4.c:38:2: error: implicit declaration of function 'pthread_barrier_init' is invalid in C99
//       [-Werror,-Wimplicit-function-declaration]
//         pthread_barrier_init(&barrier, NULL, 2);
//         ^
// 16_4.c:38:2: note: did you mean 'pthread_attr_init'?
// /Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/pthread.h:259:5: note: 'pthread_attr_init'
//       declared here
// int pthread_attr_init(pthread_attr_t *);
//     ^
// 16_4.c:54:12: error: implicit declaration of function 'ptrhead_join' is invalid in C99
//       [-Werror,-Wimplicit-function-declaration]
//         result1 = ptrhead_join(thread1, NULL);
//                   ^
// 16_4.c:54:12: note: did you mean 'pthread_join'?
// /Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/pthread.h:362:5: note: 'pthread_join'
//       declared here
// int pthread_join(pthread_t , void * _Nullable * _Nullable)
//     ^
// 16_4.c:63:2: error: implicit declaration of function 'pthread_barrier_destroy' is invalid in C99
//       [-Werror,-Wimplicit-function-declaration]
//         pthread_barrier_destroy(&barrier);
//         ^
// 16_4.c:63:2: note: did you mean 'pthread_attr_destroy'?
// /Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/pthread.h:226:5: note: 
//       'pthread_attr_destroy' declared here


int pthread_attr_destroy(pthread_attr_t *);

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// The barrier object
pthread_barrier_t barrier;
void	*thread_body_1(void	*arg)
{
	printf("A\n");
	// Wait for the other thread to join
	pthread_barrier_wait(&barrier);
	return NULL;
}

void	*thread_body_2(void	*arg)
{
	// Wait for the other thread to join
	pthread_barrier_wait(&barrier);
	printf("B\n");
	return NULL;
}

int main (int argc, char **argv)
{
	// Initialize the barrier object
	pthread_barrier_init(&barrier, NULL, 2);

	// The thread handlers
	pthread_t thread1;
	pthread_t thread2;
	
	// Create new threads
	int result1 = pthread_create(&thread1, NULL, thread_body_1, NULL);
	int result2 = pthread_create(&thread2, NULL, thread_body_2, NULL);

	if (result1 || result2)
	{
		printf("The threads could not be created. \n");
		exit (1);
	}
	// Wait for the threads to finish
	result1 = ptrhead_join(thread1, NULL);
	result2 = pthread_join(thread2, NULL);

	if (result1 || result2)
	{
		printf("The threads could not be created.\n");
		exit (2);
	}
	// Destroy the barrier object
	pthread_barrier_destroy(&barrier);
	return 0;
}