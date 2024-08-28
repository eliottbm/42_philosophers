/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:48:54 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/26 14:11:13 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	set_max_eats_lock(t_data *data)
{
	pthread_mutex_lock(&data->max_eats_lock);
	data->n_max_eats++;
	pthread_mutex_unlock(&data->max_eats_lock);
}

int	check_max_eats_lock(t_data *data)
{
	int	retval;

	pthread_mutex_lock(&data->max_eats_lock);
	retval = 0;
	if (data->n_max_eats == data->n_philos)
		retval = 1;
	pthread_mutex_unlock(&data->max_eats_lock);
	return (retval);
}

void	set_l_eat_lock(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->safe_lock);
	philo->l_eat = t_diff(data->s_time);
	pthread_mutex_unlock(&philo->safe_lock);
}

int	check_eat_lock(t_data *data, t_philo *philos, int i)
{
	int	retval;

	pthread_mutex_lock(&philos[i].safe_lock);
	retval = 0;
	if (t_diff(data->s_time) - philos[i].l_eat > data->tt_die)
		retval = 1;
	pthread_mutex_unlock(&philos[i].safe_lock);
	return (retval);
}
