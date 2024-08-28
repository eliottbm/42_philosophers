/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:16:05 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/23 18:36:09 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static void	free_mutex(t_data *data)
{
	if (data->is_inits > 0)
		pthread_mutex_destroy(&data->av_forks_lock);
	if (data->is_inits > 1)
		pthread_mutex_destroy(&data->max_eats_lock);
	if (data->is_inits > 2)
		pthread_mutex_destroy(&data->is_end_lock);
	if (data->is_inits > 3)
		pthread_mutex_destroy(&data->print_lock);
}

static void	free_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (data->is_inits > i + 4)
			pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

static void	free_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (data->is_inits > i + data->n_philos + 4)
			pthread_mutex_destroy(&data->philos[i].safe_lock);
		i++;
	}
	free(data->philos);
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->av_forks)
			free(data->av_forks);
		free_mutex(data);
		if (data->forks)
			free_forks(data);
		if (data->philos)
			free_philos(data);
		free(data);
	}
}
