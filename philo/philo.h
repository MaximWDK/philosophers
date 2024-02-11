/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:23:03 by mleonet           #+#    #+#             */
/*   Updated: 2024/02/11 11:59:57 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdatomic.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	atomic_int			has_eaten;
	_Atomic time_t		last_meal;
	pthread_t			thread_id;
	t_data				*data;
}	t_philo;

struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	time_t			start;
	atomic_int		nb_meals;
	int				all_ate;
	atomic_int		dead;
	pthread_mutex_t	*write;
	pthread_mutex_t	*forks;
	t_philo			*philos;
};

// main.c
void	*philo_life(void *philo);
void	ft_eat(t_philo *philo);
int		only_one(t_data *data);
int		wait_threads(t_data *data);

// check.c
int		ft_check_args(int argc, char **argv);
int		ft_check_arg(char *str);
void	ft_check_data(t_data *data, int argc);
void	ft_check_end(t_data *data);

// init.c
int		init_all(t_data *data, int argc, char **argv);
int		init_mutex(t_data *data);
int		create_threads(t_data *data);

// utils.c
int		ft_atoi(const char *str);
int		ft_isdigit(char c);
void	ft_usleep(time_t time);
void	ft_print_state(t_philo *philo, char *str);
void	ft_print_simple(int id, t_data *data, char *str);

// utils2.c
time_t	get_time(void);
void	philo_dead(t_philo *philo, int dead);
int		is_full(t_philo *philo);
int		ft_error(t_data *data, char *str, int type);

#endif
