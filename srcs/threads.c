/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:27:05 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/27 14:32:47 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	make_threads(t_data *data)
{
	t_philo	*p;
	int		i;

	p = data->philos;
	i = 0;
	data->s_time = gettime_ms();
	while (i < data->n_philos)
	{
		if (pthread_create(&p[i].t_id, NULL, &philo_routine, &p[i]) != 0)
			return (ft_puterror("Thread creation failed\n"), 1);
		i++;
	}
	if (pthread_create(&data->mt_id, NULL, &monitor_routine, data) != 0)
		return (ft_puterror("Thread creation failed\n"), 1);
	return (0);
}

int	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->philos[i].t_id, NULL) != 0)
			return (ft_puterror("Thread join failed\n"), 1);
		i++;
	}
	if (pthread_join(data->mt_id, NULL) != 0)
		return (ft_puterror("Thread join failed\n"), 1);
	return (0);
}
