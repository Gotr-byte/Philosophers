/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_processes_diff.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:23:36 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/25 10:09:08 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void	*routine()
{
	sleep(2);
	x += 5;
	printf("Value of x in the first routine: %d \n", x);
}
void	*routine2()
{
	printf("Value of x in the second routine: %d \n", x);
}

int	main(int argc, char	*argv[])
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL))
	{
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine2, NULL))
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
	return (0);
}
