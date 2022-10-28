/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_thread_diff.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:26:25 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/19 19:41:18 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main(int argc, char *argv[])
{
	int x = 2;
	int pid = fork();
	if (pid == -1)
	{
		return (1);
	}
	if (pid == 0)
	{
		x++;
	}
	sleep(2);
	printf("Value of x: %d\n", x);
	printf("Process id %d\n", getpid());
	if(pid != 0)
	{
		wait(NULL);
	}
	return (0);
}