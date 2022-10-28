/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:11:28 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/19 19:22:41 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*routine()
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
	return (NULL);
}

int	main(int argc, char*argv[])
{
	pthread_t	t1;
	pthread_t	t2;
	if (pthread_create(&t1, NULL, &routine, NULL)!=0)
	{
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
	{
		return (2);
	}
	if (pthread_join(t1, NULL) != 0)
	{
		return (3);
	}
	if (pthread_join(t2, NULL) != 0)
	{
		return (4);
	}
	return (0);
}
