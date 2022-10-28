/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/28 16:50:22 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

//will need to replace calloc and atoi with ft_atoi
//libeartor function from so_long
//hard code for one philosopoher

// void	timestamp()

// pthread_mutex_t eatex;

void *eating(void *arg)
{
	t_philosopher 	*philosopher;
	struct timeval 	start, end;
	static int				i;

	philosopher = (t_philosopher *)arg;
	philosopher->time_to_die_curr = philosopher->time_to_die_set;
	philosopher->sleep_time_curr = philosopher->sleep_time_set;
	while (TRUE)
	{
		if (philosopher->time_to_die_curr == 0)
		{
			gettimeofday(&start, NULL);
			printf("%ld %d has died\n", \
			(start.tv_sec * 1000 + start.tv_usec / 1000),\
			philosopher->nb);
			exit(0);
		}
		if (philosopher->sleep_time_curr > 0)
		{
			gettimeofday(&start, NULL);
			usleep(philosopher->sleep_time_curr);
			philosopher->time_to_die_curr = philosopher->time_to_die_curr - philosopher->sleep_time_curr;
			philosopher->sleep_time_curr = 0;
			printf("%ld %d is sleeping\n", \
			(start.tv_sec * 1000 + start.tv_usec / 1000),\
			philosopher->nb);
		}
		else
		{
			gettimeofday(&start, NULL);
			printf("%ld %d is taking his time thinking\n", \
			(start.tv_sec * 1000 + start.tv_usec / 1000),\
			philosopher->nb);
		}
		pthread_mutex_lock(&philosopher->next->fork);
		pthread_mutex_lock(&philosopher->fork);
		gettimeofday(&start, NULL);
		usleep(philosopher->gorge_time);
		philosopher->sleep_time_curr = philosopher->sleep_time_set;
		gettimeofday(&end, NULL);
		pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(&philosopher->next->fork);
		printf("%ld %d is eating\n",\
		(start.tv_sec * 1000 + start.tv_usec / 1000),\
		philosopher->nb);
	
		i++;
	}
	return (NULL);
}
// void	print_table(t_philosopher	**last)
// {
// 		printf("Number: %d\nIndicator: %d\nTime to die: %d\nTime to eat: %d\nTime to sleep: %d\nEat times: %d\n",\
// 		last->nb, last->indicator, last->time_to_die_set, last->gorge_time, last->sleep_time_set, last->eat_times);
// 		last = last->next;
// }
void	release_list(t_philosopher **lst)
{
	t_philosopher	*former;
	t_philosopher	*current;

	former = *lst;
	current = *lst;
	while (current->indicator != LAST)
	{
		former = current;
		current = current->next;
		free(former);
	}
	free(current);
}

void	weave_threads(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_create(&last->pt_id, NULL, eating, last);
		last = last->next;
	}
	pthread_create(&last->pt_id, NULL, eating, last);
}

void	join_threads(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_join(last->pt_id, NULL);
		last = last->next;
	}
	pthread_join(last->pt_id, NULL);
}

void	summon_mutexes(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_mutex_init(&(last->fork), NULL);
		last = last->next;
	}
	pthread_mutex_init(&(last->fork), NULL);
}

void	expell_mutexes(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_mutex_destroy(&(last->fork));
		last = last->next;
	}
	pthread_mutex_destroy(&(last->fork));
}

void	traverse_table(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		printf("Number: %d\nIndicator: %d\nTime to die: %d\nTime to eat: %d\nTime to sleep: %d\nEat times: %d\n",\
		last->nb, last->indicator, last->time_to_die_set, last->gorge_time, last->sleep_time_set, last->eat_times);
		last = last->next;
	}
	printf("Number: %d\nIndicator: %d\nTime to die: %d\nTime to eat: %d\nTime to sleep: %d\nEat times: %d\n",\
	last->nb, last->indicator, last->time_to_die_set, last->gorge_time, last->sleep_time_set, last->eat_times);
}

void	last_point_first(t_philosopher **lst)
{
	t_philosopher	*last;
	t_philosopher	*first;

	last = *lst;
	while (last)
	{
		if (last->next == NULL)
			break ;
		last->indicator = NOT_LAST;
		last = last->next;
	}
	last->indicator = LAST;
	first = *lst;
	last->next = first;
	return ;
}

void	local_lstadd_back(t_philosopher **lst, t_philosopher *new)
{
	t_philosopher	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last)
	{
		if (last->next == NULL)
			break ;
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
	return ;
}

t_philosopher	*ft_lstnew_int(int content, int die, int eat, int sleep, int times)
{
	t_philosopher	*tmp;

	tmp = (t_philosopher *)ft_calloc(1, sizeof(t_philosopher));
	if (!tmp)
		return (NULL);
	if (!content)
		tmp->nb = 0;
	if (tmp)
	{
		tmp->nb = content;
		tmp->time_to_die_set = die;
		tmp->gorge_time = eat;
		tmp->sleep_time_set = sleep;
		tmp->eat_times = times;
		tmp->next = NULL;
	}
	return (tmp);
}

int main (int	ac, char **av)
{
	int				i;
	t_philosopher	*table;
	if (ac == 1)
		exit(2);
	i = 1;
	while	(i <= ft_atoi(av[1]))
	{
		local_lstadd_back(&table, ft_lstnew_int(i, ft_atoi(av[2]), ft_atoi(av[3]), ft_atoi(av[4]), ft_atoi(av[5])));
		i++;
	}
	last_point_first(&table);
	traverse_table(&table);
	summon_mutexes(&table);
	weave_threads(&table);
	join_threads(&table);
	expell_mutexes(&table);
	release_list(&table);
	return(0);
}
