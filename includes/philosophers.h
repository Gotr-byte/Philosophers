/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:33:53 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/10 14:44:13 by pbiederm         ###   ########.fr       */
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
# include <limits.h>
# include "philosophers.h"

# define TRUE 1
# define NOT_LAST 1
# define LAST 0
# define END 0
# define NOT_END 1
# define NOT_EATEN_FULL 0
# define EATEN_FULL 1
# define SET_SCOPE 4294967295

typedef struct s_philo
{
	pthread_t			pt_id;
	int					nb;
	int					end;
	int					start;
	int					number_of_philosophers;
	int					gorge_time;
	int					sleep_time_set;
	int					indicator;
	long				last_eaten;
	long				zero_time;
	int					eat_times;
	int					eaten_full_value;
	int					number_of_full_philosophers;
	pthread_mutex_t		last_eaten_mutex;	
	pthread_mutex_t		fork;
	pthread_mutex_t		eaten_full_mutex;
	pthread_mutex_t		end_mutex;
	struct s_philo		*next;
	struct s_timer		*timer;
}t_philosopher;

typedef struct s_timer
{
	pthread_t			id;
	t_philosopher		*philosophers;
	long				timer_zero_time;
	int					time_to_die;
	int					number_of_philosophers_in_timer;
}t_timer;

void				free_lst(t_philosopher	*head);
unsigned long long	ft_atoi_t(const char *str);
void				*ft_calloc(size_t count, size_t size);
t_philosopher		*ft_lstnew_int(char **av, \
int content, t_timer *timer);
void				local_lstadd_back(t_philosopher **lst, t_philosopher *new);
void				last_point_first(t_philosopher **lst);
void				traverse_table(t_philosopher **lst, long curr_time);
void				expell_mutexes(t_philosopher **lst);
void				summon_mutexes(t_philosopher **lst);
void				join_threads(t_philosopher **lst);
void				weave_threads(t_philosopher **lst);
void				release_list(t_philosopher **lst, t_timer *reaper);
void				*living(void *arg);
void				detach_threads(t_philosopher **lst);
long				get_time(void);
int					argument_number_check(int ac, char **av);
int					ft_isdigit_char(char c);
void				eating(t_philosopher **arg);
void				sleeping(t_philosopher **arg);
void				thinking(t_philosopher **arg);
void				*living(void *arg);
void				*hourglass(void *timer);
void				print_safeguard(t_philosopher **philosopher_struct);
void				philosopher_do(t_philosopher **philosopher);
void				philosopher_sleep(t_philosopher **philosopher, long x_time);
int					single_philosopher(char **av);
t_philosopher		*initialization_step(int ac, char **av, \
t_philosopher *table, t_timer *timer);
void				have_all_eaten(t_timer **table);
void				befork_safeguard(t_philosopher **philosopher_struct);
void				get_values(t_philosopher **lst);
void				eating_safeguard(t_philosopher **recieve);
void				the_end(t_philosopher	**recieve);
void				eating_ende(t_timer **recieve);
void				ende(t_timer **recieve);
#endif