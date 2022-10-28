/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_talk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:18:58 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/19 16:21:58 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned long addall()
{
	int i;
	unsigned long sum;

	i = 0;
	sum = 0;
	while (i < 10000000)
	{
		sum += i;
		i++;
	}
	return(sum);
}

int main()
{
	unsigned long sum;
	srandom(time(NULL));
	sum = addall();
	printf("%lu\n", sum);
}