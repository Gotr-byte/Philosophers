/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_exec_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:07:59 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/24 12:15:24 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>

int	main()
{
	struct timeval start, end;
	gettimeofday(&start, NULL);

	for (int i = 0; i < 1e5; i++)
	{
		gettimeofday(&end, NULL);
		printf("Time taken to count to 10ˆ5 is: %ld micro seconds\n"),\
		((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	}
}