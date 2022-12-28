/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:33:53 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/28 13:52:12 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>

# define TRUE 1
# define NOT_LAST 1
# define LAST 0

typedef struct s_philo
{
	pthread_t			pt_id;
	int					nb;
	int					gorge_time;
	int					sleep_time_set;
	int					sleep_time_curr;
	int					time_to_die_set;
	int					indicator;
	long				last_eaten;
	long				zero_time;
	int					eat_times;
	// t_eatex				*eatex;
	pthread_mutex_t		is_dead;	
	pthread_mutex_t		fork;
	// struct t_eatex		*eatex;
	struct s_philo		*next;
}t_philosopher;

// typedef struct s_eatex
// {
// 	pthread_mutex_t	test;
// 	pthread_mutex_t	fork;
// }t_eatex

void			free_lst(t_philosopher	*head);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
t_philosopher	*ft_lstnew_int(int content, int die, int eat, int sleep);
void			local_lstadd_back(t_philosopher **lst, t_philosopher *new);
void			last_point_first(t_philosopher **lst);
void			traverse_table(t_philosopher **lst, long curr_time);
void			expell_mutexes(t_philosopher **lst);
void			summon_mutexes(t_philosopher **lst);
void			join_threads(t_philosopher **lst);
void			weave_threads(t_philosopher **lst);
void			release_list(t_philosopher **lst);
void			*living(void *arg);
void			detach_threads(t_philosopher **lst);
#endif