/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:58:30 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/18 19:30:42 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// The POSIX standard header for using pthread libreary
#include <pthread.h>

// The semaphores are not exposed through pthread.h
#include <semaphore.h>
// The main pointer addressin a semaphore object 
// used to synchdronize the access to the shared state.
sem_t *semaphore;

void	*thread_body_1(void	*arg)
{
	//Obtain a pointer to the shared variable
	int	*shared_var_ptr = (int*)arg;
	// Waiting for the semaphore
	sem_wait(semaphore);
	// Increment the shared variable by 1 by writing directly to its memory address
	(*shared_var_ptr)++;
	printf("%d\n", *shared_var_ptr);
	// Release the semaphore
	sem_post (semaphore);
	return (NULL);
}

void	*thread_body_2(void *arg)
{
	// Obtain a pointer to the shared variable
	int *shared_var_ptr = (int*)arg;
	// Waiting for the semaphore
	sem_wait(semaphore);
	// Incerment the shared variable by 1 by writing directly to its memory address
	(*shared_var_ptr) += 2;
	printf("%d\n", *shared_var_ptr);
	// release the semaphore
	sem_post(semaphore);
	return (NULL);
}

int main(int argc, char** argv)
{
	// The shared variable
	int shared_var = 0;
	
	// The thread handlers
	pthread_t thread1;
	pthread_t thread2;

	#ifdef __APPLE__
	// Unnamed semaphores are not supported in OS/X. Therefore
	// we need to initialize the semaphore like a named one using
	// sem_open function.
	semaphore = sem_open ("sem0", O_CREAT | O_EXCL, 0644, 1);
	#else
	sem_t local_semaphore;
	semaphore = &local_semaphore;
	// Initialize the semaphore as a mutex (binary semaphore)
	sem_init(semaphore, 0, 1);
	#endif
	
	// Create new threads
	int result1 = pthread_create(&thread1, NULL, thread_body_1, &shared_var);
	int result2 = pthread_create(&thread2, NULL, thread_body_2, &shared_var);

	if (result1 || result2)
	{
		printf("The threads could not be created.\n");
		exit(1);
	}
	// Wait for the threads to finish
	result1 = pthread_join(thread1, NULL);
	result2 = pthread_join(thread2, NULL);

	if (result1 || result2)
	{
		printf("The threads could not be joined.\n");
		exit(2);
	}
	#ifdef __APPLE__
		sem_close(semaphore);
	#else
		sem_destroy(semaphore);
	#endif

	return (0);
}
