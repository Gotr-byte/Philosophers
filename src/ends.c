/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ends.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:26:29 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/06 15:33:32 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	the_end(t_philosopher	**recieve)
{
	t_philosopher	*philosopher;

	philosopher = *recieve;
	pthread_mutex_lock(&philosopher->end_mutex);
	if(philosopher->end == END)
	{
		printf("THE END HAS COME\n");
		printf("To philosopher: %d\n", philosopher->nb);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philosopher->end_mutex);
}