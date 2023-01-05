/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:16:34 by pbiederm          #+#    #+#             */
/*   Updated: 2023/01/05 18:27:29 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	get_values(t_philosopher **lst)
{
	t_philosopher	*last;
	long			start_time;

	last = *lst;
	start_time = get_time() + 5000;
	while (last->indicator != LAST)
	{
		last->zero_time = start_time;
		last->hourglass_zero_time = start_time;
		last->hourglass->hourglass_zero_time = start_time;
		last->last_eaten = start_time;
		last->start = 0;
		last->hourglass->start = 0;
		last = last->next;
	}
	last->zero_time = start_time;
	last->hourglass_zero_time = start_time;
	last->hourglass->hourglass_zero_time = start_time;
	last->last_eaten = start_time;
	last->start = 0;
	last->hourglass->start = 0;
}
