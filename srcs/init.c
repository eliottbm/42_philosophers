/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:50:48 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/27 15:07:22 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static int	data_init4(t_data *data)
{
	if (pthread_mutex_init(&data->av_forks_lock, NULL) != 0)
		return (1);
	data->is_inits++;
	if (pthread_mutex_init(&data->max_eats_lock, NULL) != 0)
		return (1);
	data->is_inits++;
	if (pthread_mutex_init(&data->is_end_lock, NULL) != 0)
		return (1);
	data->is_inits++;
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	data->is_inits++;
	return (0);
}

static int	data_init3(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
			return (1);
		data->is_inits++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->philos[i].safe_lock, NULL) != 0)
			return (1);
		data->is_inits++;
		data->av_forks[i] = 'y';
		data->philos[i].p_id = i + 1;
		data->philos[i].n_eats = 0;
		data->philos[i].l_eat = -1;
		data->philos[i].data = data;
		i++;
	}
	data->av_forks[i] = '\0';
	return (0);
}

static int	data_init2(t_data *data)
{
	const int	tt_min = ft_min(data->tt_eat, data->tt_sleep);

	if (data->tt_die - (data->tt_eat + data->tt_sleep) < tt_min)
		data->tt_think = 1;
	else
		data->tt_think = tt_min;
	data->philos = malloc(sizeof(t_philo) * (data->n_philos));
	if (!data->philos)
		return (ft_puterror("Philos malloc failed\n"), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->n_philos));
	if (!data->forks)
		return (ft_puterror("Forks malloc failed\n"), 1);
	data->av_forks = malloc(sizeof(char) * (data->n_philos + 1));
	if (!data->av_forks)
		return (ft_puterror("Forks malloc failed\n"), 1);
	data->is_end = 0;
	data->n_max_eats = 0;
	return (0);
}

int	data_init(t_data *data, int ac, char **av)
{
	data->philos = NULL;
	data->forks = NULL;
	data->av_forks = NULL;
	data->is_inits = 0;
	if (data_init4(data))
		return (1);
	data->n_philos = ft_atoi(av[1]);
	if (data->n_philos < 1)
		return (ft_puterror("Wrong args\n"), 1);
	data->tt_die = ft_atoi(av[2]);
	data->tt_eat = ft_atoi(av[3]);
	data->tt_sleep = ft_atoi(av[4]);
	data->max_eats = -1;
	if (ac == 6)
		data->max_eats = ft_atoi(av[5]);
	if (data->tt_die < 1 || data->tt_eat < 1
		|| data->tt_sleep < 1
		|| (ac == 6 && data->max_eats < 1))
		return (ft_puterror("Wrong args\n"), 1);
	if (data_init2(data))
		return (1);
	if (data_init3(data))
		return (1);
	return (0);
}
