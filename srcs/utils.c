/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:09:47 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/28 23:45:48 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	ft_puterror(char *s)
{
	size_t	i;

	i = 0;
	write(2, "Error\n", 6);
	while (s[i])
	{
		write(2, &(s[i]), 1);
		i++;
	}
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_atoi(char const *str)
{
	size_t	i;
	long	rez;

	i = 0;
	rez = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		rez *= 10;
		rez += (str[i] - '0');
		i++;
	}
	if (rez > 2147483647)
		return (0);
	return (rez);
}

int	gettime_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_puterror("Failed to get time\n"), 1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	t_diff(int ms)
{
	return (gettime_ms() - ms);
}
