/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:10:11 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/21 20:19:15 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void	*roll_dice()
{
	int value = (rand() % 6) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	sleep(2);
	pritnf("Thread result %d\n", value);
	pthread_exit((void*)result);
}

int	main(int argc, char *argv[])
{
	int	*res;
	srand(time(NULL));
	pthread_t th;

	if(pthread_create(&th, NULL, &roll_dice, NULL) != 0)
	{
		return (1);
	}
	//pthread_exit(0);
	if (pthread_join(th, (void	**)&res) != 0)
	{
		return (2);
	}
	printf("Main res %p\n", res);
	printf("Result %d\n", *res);
	free (res);
	return (0);
}