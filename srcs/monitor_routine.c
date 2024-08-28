/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:37:49 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/28 23:46:50 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static int	end_check(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
	{
		if (check_max_eats_lock(data))
		{
			set_end_lock(data);
			return (1);
		}
		if (check_eat_lock(data, philos, i))
		{
			set_end_lock(data);
			print_lock(data, philos[i].p_id, "died");
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *void_data)
{
	t_data	*data;

	data = (t_data *)void_data;
	while (1 == 1)
	{
		if (end_check(data))
			break ;
		usleep(500);
	}
	return (NULL);
}
