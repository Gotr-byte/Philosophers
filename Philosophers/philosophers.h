#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

# define 	TRUE 1
typedef struct	s_philo
{
	pthread_t		pt_id;
	char			*name;
	int				gorge_time;
	int				sleep_time_set;
	int				sleep_time_curr;
	int				think_time;
	int				time_to_die_set;
	int				time_to_die_curr;
	pthread_mutex_t	fork;
	struct s_philo	*next;
}t_philosopher;
#endif