#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>


typedef struct s_time
{
	long			curr_time;
}t_time;
//
typedef struct	s_philo
{
	pthread_t	pt_id;
	char		*name;
	int			gorge_time;
	int			sleep_time_set;
	int			sleep_time_curr;
	int			think_time;
	int			time_to_die;
	// t_time		*ptr;
	//mutex to point to something
}t_philosopher;
#endif