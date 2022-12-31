/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:32:26 by pbiederm          #+#    #+#             */
/*   Updated: 2022/12/31 14:54:51 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	release_list(t_philosopher **lst, t_hourglass *release)
{
	t_philosopher	*former;
	t_philosopher	*current;

	former = *lst;
	current = *lst;
	while (current->indicator != LAST)
	{
		former = current;
		current = current->next;
		free(former);
	}
	free(current);
	free(release);
}
