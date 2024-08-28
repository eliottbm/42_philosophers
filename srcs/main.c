/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:00:58 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/20 15:02:32 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_puterror("Data malloc failed\n"), 1);
	if (ac < 5 || ac > 6 || data_init(data, ac, av))
		return (free_data(data), 1);
	if (make_threads(data))
		return (free_data(data), 1);
	wait_threads(data);
	return (free_data(data), 0);
}
