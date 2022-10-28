#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
# define 	TRUE 1
# define	NOT_LAST 1
# define	LAST 0

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
	pthread_mutex_t	fork;
	struct s_philo	*next;
}t_philosopher;

void	free_lst(t_philosopher	*head);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
#endif