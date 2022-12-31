/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:33:53 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/31 17:05:17 by pbiederm         ###   ########.fr       */
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

# define TRUE 1
# define NOT_LAST 1
# define LAST 0
# define END 0
# define NOT_END 1
# define SET_SCOPE 4294967295

typedef struct s_hourglass
{
	int	end;
}t_hourglass;

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
	long				hourglass_zero_time;
	int					eat_times;
	int					eaten_full_value;
	pthread_mutex_t		last_eaten_mutex;	
	pthread_mutex_t		fork;
	pthread_mutex_t		end;
	pthread_mutex_t		eaten_full_mutex;
	struct s_philo		*next;
	struct s_hourglass	*hourglass;
}t_philosopher;



void				free_lst(t_philosopher	*head);
unsigned long long	ft_atoi_t(const char *str);
void				*ft_calloc(size_t count, size_t size);
t_philosopher		*ft_lstnew_int(int content, int die, int eat, int sleep, t_hourglass **hourglass_recieve);
void				local_lstadd_back(t_philosopher **lst, t_philosopher *new);
void				last_point_first(t_philosopher **lst);
void				traverse_table(t_philosopher **lst, long curr_time);
void				expell_mutexes(t_philosopher **lst);
void				summon_mutexes(t_philosopher **lst);
void				join_threads(t_philosopher **lst);
void				weave_threads(t_philosopher **lst);
void				release_list(t_philosopher **lst, t_hourglass *release);
void				*living(void *arg);
void				detach_threads(t_philosopher **lst);
long				get_time(void);
int					argument_number_check(int ac, char **av);
int					ft_isdigit_char(char c);
void				eating(t_philosopher **arg);
void				sleeping(t_philosopher **arg);
void				thinking(t_philosopher **arg);
void				*living(void *arg);
void				hourglass(t_philosopher **table, t_hourglass **hourglass_recieve);
void				print_safeguard(t_philosopher **philosopher_struct);
void				philosopher_do(t_philosopher **philosopher, long x_time);
void				philosopher_sleep(t_philosopher **philosopher, long x_time);
#endif