/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:16:34 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/08 18:22:18 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	get_values(t_philosopher **lst)
{
	t_philosopher	*last;
	long			start_time;
	long			traverse;

	last = *lst;
	traverse = last->number_of_philosophers;
	start_time = get_time() + 5000;
	last->timer->timer_zero_time = start_time;
	while (traverse > 0)
	{
		last->zero_time = start_time;
		last->last_eaten = start_time;
		last->start = 0;
		last = last->next;
		traverse--;
	}
}
