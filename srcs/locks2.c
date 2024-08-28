/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:36:08 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/23 17:40:25 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	set_end_lock(t_data *data)
{
	pthread_mutex_lock(&data->is_end_lock);
	data->is_end = 1;
	pthread_mutex_unlock(&data->is_end_lock);
}

int	check_end_lock(t_data *data)
{
	int	retval;

	pthread_mutex_lock(&data->is_end_lock);
	retval = 0;
	if (data->is_end)
		retval = 1;
	pthread_mutex_unlock(&data->is_end_lock);
	return (retval);
}

void	print_lock(t_data *data, int p_id, char *str)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%d %d %s\n", t_diff(data->s_time), p_id, str);
	pthread_mutex_unlock(&data->print_lock);
}

void	forks_unlock(t_data *data, int l_i, int r_i, int which)
{
	if (which == 1)
		pthread_mutex_unlock(&data->av_forks_lock);
	if (which == 2)
	{
		pthread_mutex_unlock(&data->forks[l_i]);
		pthread_mutex_unlock(&data->av_forks_lock);
	}
	if (which == 3)
	{
		pthread_mutex_unlock(&data->forks[l_i]);
		pthread_mutex_unlock(&data->forks[r_i]);
	}
}
