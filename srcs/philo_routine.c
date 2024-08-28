/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:28:29 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/27 14:41:53 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static int	philo_safe_wait(t_data *data, int ms)
{
	int	t_time;

	t_time = gettime_ms();
	while (t_diff(t_time) < ms)
	{
		if (check_end_lock(data))
			return (1);
		usleep(500);
	}
	return (0);
}

static int	philo_eat3(t_philo *philo, t_data *data, int l_i, int r_i)
{
	data->av_forks[l_i] = 'n';
	data->av_forks[r_i] = 'n';
	if (check_end_lock(data))
		return (forks_unlock(data, l_i, r_i, 1), 1);
	pthread_mutex_lock(&data->forks[l_i]);
	print_lock(data, philo->p_id, "has taken a fork");
	if (l_i == r_i)
		if (philo_safe_wait(data, (data->tt_die * 2)))
			return (forks_unlock(data, l_i, r_i, 2), 1);
	pthread_mutex_lock(&data->forks[r_i]);
	print_lock(data, philo->p_id, "has taken a fork");
	pthread_mutex_unlock(&data->av_forks_lock);
	return (0);
}

static int	philo_eat2(t_philo *philo, t_data *data, int l_i, int r_i)
{
	if (philo_eat3(philo, data, l_i, r_i))
		return (1);
	if (check_end_lock(data))
		return (forks_unlock(data, l_i, r_i, 3), 1);
	set_l_eat_lock(data, philo);
	print_lock(data, philo->p_id, "is eating");
	if (philo_safe_wait(data, data->tt_eat))
		return (forks_unlock(data, l_i, r_i, 3), 1);
	philo->n_eats++;
	if (philo->n_eats == data->max_eats)
		set_max_eats_lock(data);
	pthread_mutex_lock(&data->av_forks_lock);
	data->av_forks[l_i] = 'y';
	data->av_forks[r_i] = 'y';
	pthread_mutex_unlock(&data->forks[l_i]);
	pthread_mutex_unlock(&data->forks[r_i]);
	pthread_mutex_unlock(&data->av_forks_lock);
	return (0);
}

static void	philo_eat(t_philo *philo)
{
	t_data	*data;
	int		l_i;
	int		r_i;

	data = philo->data;
	l_i = philo->p_id - 1;
	if (philo->p_id == 1)
		r_i = philo->data->n_philos - 1;
	else
		r_i = philo->p_id - 2;
	while (1 == 1)
	{
		if (check_end_lock(data))
			return ;
		pthread_mutex_lock(&data->av_forks_lock);
		if (data->av_forks[l_i] == 'y' && data->av_forks[r_i] == 'y')
		{
			philo_eat2(philo, data, l_i, r_i);
			return ;
		}
		pthread_mutex_unlock(&data->av_forks_lock);
		usleep(500);
	}
}

void	*philo_routine(void *void_philo)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	data = philo->data;
	set_l_eat_lock(data, philo);
	while (1 == 1)
	{
		philo_eat(philo);
		if (check_end_lock(data))
			return (NULL);
		print_lock(data, philo->p_id, "is sleeping");
		if (philo_safe_wait(data, data->tt_sleep))
			return (NULL);
		if (check_end_lock(data))
			return (NULL);
		print_lock(data, philo->p_id, "is thinking");
		if (philo_safe_wait(data, data->tt_think))
			return (NULL);
	}
	return (NULL);
}
