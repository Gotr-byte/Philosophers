/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:01 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/28 15:48:21 by pbiederm         ###   ########.fr       */
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

// void *eating(void *arg)
// {
// 	t_philosopher 	*philosopher;
// 	struct timeval 	start, end;
// 	static int				i;

// 	philosopher = (t_philosopher *)arg;
// 	while (TRUE)
// 	{
// 		if (philosopher->time_to_die_curr == 0)
// 		{
// 			gettimeofday(&start, NULL);
// 			printf("%ld %s has died\n", \
// 			(start.tv_sec * 1000 + start.tv_usec / 1000),\
// 			(char *)philosopher->name);
// 			exit(0);
// 		}
// 		if (philosopher->sleep_time_curr > 0)
// 		{
// 			gettimeofday(&start, NULL);
// 			usleep(philosopher->sleep_time_curr);
// 			philosopher->time_to_die_curr = philosopher->time_to_die_curr - philosopher->sleep_time_curr;
// 			philosopher->sleep_time_curr = 0;
// 			printf("%ld %s is sleeping\n", \
// 			(start.tv_sec * 1000 + start.tv_usec / 1000),\
// 			(char *)philosopher->name);
// 		}
// 		else
// 		{
// 			gettimeofday(&start, NULL);
// 			printf("%ld %s is taking his time thinking\n", \
// 			(start.tv_sec * 1000 + start.tv_usec / 1000),\
// 			(char *)philosopher->name);
// 		}
// 		pthread_mutex_lock(&philosopher->next->fork);
// 		pthread_mutex_lock(&philosopher->fork);
// 		gettimeofday(&start, NULL);
// 		usleep(philosopher->gorge_time);
// 		philosopher->sleep_time_curr = philosopher->sleep_time_set;
// 		gettimeofday(&end, NULL);
// 		pthread_mutex_unlock(&philosopher->fork);
// 		pthread_mutex_unlock(&philosopher->next->fork);
// 		printf("%ld %s is eating\n",\
// 		(start.tv_sec * 1000 + start.tv_usec / 1000),\
// 		(char *)philosopher->name);
	
// 		i++;
// 	}

// 	return (arg);
// }
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
	free(cu)
}
void	summon_mutexes(t_philosopher **lst)
{
	t_philosopher	*last;

	last = *lst;
	while (last->indicator != LAST)
	{
		pthread_mutex_init(&(last->fork), NULL);
	}
	pthread_mutex_init(&(last->fork), NULL);
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

// void	summon_mutex()
// {
	
// }

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
	// free_lst(&table);
	// free(table);
	return(0);
	
	// t_philosopher	*Konfucjusz = NULL;
	// t_philosopher	*Marek = NULL;
	// t_philosopher	*Platon = NULL;

	// Platon = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	// Konfucjusz = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	// Marek = (t_philosopher*)calloc(1, sizeof(t_philosopher));
	// Konfucjusz->next = Platon;
	// Platon->next = Marek;
	// Marek->next = Konfucjusz;
	// pthread_mutex_init(&(Konfucjusz->fork), NULL);
	// pthread_mutex_init(&(Marek->fork), NULL);
	// pthread_mutex_init(&(Platon->fork), NULL);
	// Konfucjusz->name = (char *)calloc(11, sizeof(char));
	// Marek->name = (char *)calloc(6, sizeof(char));
	// Platon->name = (char *)calloc(7, sizeof(char));
	// Konfucjusz->name = "Konfucjusz";
	// Marek->name = "Marek";
	// Platon->name = "Platon";
	// Konfucjusz->gorge_time = 1000000;
	// Marek->gorge_time = 1000000;
	// Platon->gorge_time = 1000000;
	// Konfucjusz->sleep_time_set = 2000000;
	// Marek->sleep_time_set = 2000000;
	// Platon->sleep_time_set = 2000000;
	// Konfucjusz->time_to_die_curr = 10000000;
	// Marek->time_to_die_curr = 10000000;
	// Platon->time_to_die_curr = 10000000;
	// pthread_create(&Konfucjusz->pt_id, NULL, eating, Konfucjusz);
	// pthread_create(&Marek->pt_id, NULL, eating, Marek);
	// pthread_create(&Platon->pt_id, NULL, eating, Platon);
	// pthread_join(Konfucjusz->pt_id, NULL);
	// pthread_join(Marek->pt_id, NULL);
	// pthread_join(Platon->pt_id, NULL);
	// pthread_mutex_destroy(&(Konfucjusz->fork));
	// pthread_mutex_destroy(&(Marek->fork));
	// pthread_mutex_destroy(&(Platon->fork));
	return (0);
}
