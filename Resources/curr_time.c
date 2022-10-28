/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curr_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:01:09 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/24 12:05:52 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int main ()
{
	struct timeval	tv;
	time_t			t;
	struct			tm *info;
	char			buffer[64];

	gettimeofday(&tv, NULL);
	t = tv.tv_sec;

	info = localtime(&t);
	printf("%s", asctime(info));
	strftime (buffer, sizeof buffer, "Today is %A, %B %d\n", info);
	printf("%s", buffer);
	strftime (buffer, sizeof buffer, "The time is %I:%M %p. 'n", info);
	printf("%s", buffer);

	return (0);
}