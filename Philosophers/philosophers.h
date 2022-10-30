/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:33:53 by pbiederm          #+#    #+#             */
/*   Updated: 2022/10/30 16:10:52 by pbiederm         ###   ########.fr       */
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

#define TRUE 1
#define NOT_LAST 1
#define LAST 0

typedef struct	s_philo
{
	pthread_t		pt_id;
	int				nb;
	int				eat_times;
	int				die;
	int				gorge_time;
	int				sleep_time_set;
	int				sleep_time_curr;
	int				time_to_die_set;
	int				time_to_die_curr;
	int				indicator;
	long			zero_time;
	pthread_mutex_t	fork;
	struct s_philo	*next;
}t_philosopher;

void			free_lst(t_philosopher	*head);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
t_philosopher	*ft_lstnew_int(int content, int die, int eat, int sleep, int times);
void			local_lstadd_back(t_philosopher **lst, t_philosopher *new);
void			last_point_first(t_philosopher **lst);
void	traverse_table(t_philosopher **lst, long curr_time);
void			expell_mutexes(t_philosopher **lst);
void			summon_mutexes(t_philosopher **lst);
void			join_threads(t_philosopher **lst);
void			weave_threads(t_philosopher **lst);
void			release_list(t_philosopher **lst);
void			*eating(void *arg);
#endif