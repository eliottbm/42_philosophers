/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:58:53 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/27 14:46:13 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		t_id;
	int				p_id;
	int				l_eat;
	int				n_eats;
	struct s_data	*data;
	pthread_mutex_t	safe_lock;
}					t_philo;

typedef struct s_data
{
	int				is_inits;
	pthread_t		mt_id;
	int				is_end;
	int				s_time;
	int				n_philos;
	int				n_max_eats;
	int				max_eats;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tt_think;
	char			*av_forks;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	av_forks_lock;
	pthread_mutex_t	max_eats_lock;
	pthread_mutex_t	is_end_lock;
	pthread_mutex_t	print_lock;
}					t_data;

/* INITS */
int		data_init(t_data *data, int ac, char **av);

/* ROUTINES */
void	*philo_routine(void *void_philo);
void	*monitor_routine(void *void_data);

/* THREADS */
int		make_threads(t_data *data);
int		wait_threads(t_data *data);

/* LOCKS */
int		check_eat_lock(t_data *data, t_philo *philos, int i);
int		check_end_lock(t_data *data);
int		check_max_eats_lock(t_data *data);
void	set_l_eat_lock(t_data *data, t_philo *philo);
void	set_max_eats_lock(t_data *data);
void	set_end_lock(t_data *data);
void	print_lock(t_data *data, int p_id, char *str);
void	forks_unlock(t_data *data, int l_i, int r_i, int which);

/* UTILS */
void	free_data(t_data *data);
void	ft_puterror(char *s);
int		ft_min(int a, int b);
int		ft_atoi(char const *str);
int		gettime_ms(void);
int		t_diff(int ms);

#endif