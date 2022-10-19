/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:27:22 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/13 17:28:59 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// The POSIX standard header for using pthread library
#include <pthread.h>
// This function contains the logic which should be run as
// the body of a separate thread
void *thread_body(void *arg)
{
	char	*str = (char*)arg;
	printf("%s\n", str);
	return NULL;
}

int main (int argc, char **argv)
{
	//The thread handlers
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	// Create new threads
	int result1 = pthread_create(&thread1, NULL, thread_body, "Apple");
	int result2 = pthread_create(&thread2, NULL, thread_body, "Orange");
	int result3 = pthread_create(&thread3, NULL, thread_body, "Lemon");
	
	// If the thread creation did not succeed
	if (result1 || result2 || result3)
	{
		printf("The threads could not be created.\n");
		exit(1);
	}
	// Detach the thread
	// result = pthread_detach(thread);
	// If detaching the thread did not succeed

	// result1 = pthread_join(thread1, NULL);
	result2 = pthread_join(thread2, NULL);
	result3 = pthread_join(thread3, NULL);
	// If joining the thread did not succed
	if (result1 || result2 || result3)
	{
		printf("The threads could not be joined.\n");
		exit (2);
	}
	// pthread_exit(NULL);
	return (0);
}