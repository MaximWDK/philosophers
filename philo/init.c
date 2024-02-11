/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:23:49 by mleonet           #+#    #+#             */
/*   Updated: 2024/02/11 01:50:28 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->death = NULL;
	data->write = NULL;
	data->forks = NULL;
	data->dead = 0;
	data->philos = malloc(sizeof(*data->philos) * data->nb_philos);
	if (!data->philos)
		return (ft_error(data, "Error: malloc failed\n", 0));
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	else
		data->nb_meals = -1;
	ft_check_data(data, argc);
	if (init_mutex(data) != 0)
		return (1);
	data->start = get_time();
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (ft_error(data, "Error: malloc failed\n", 0));
	data->death = malloc(sizeof(pthread_mutex_t));
	if (!data->death)
		return (ft_error(data, "Error: malloc failed\n", 0));
	data->write = malloc(sizeof(pthread_mutex_t));
	if (!data->write)
		return (ft_error(data, "Error: malloc failed\n", 0));
	i = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_error(data, "Error: pthread_mutex_init failed\n", i));
	}
	if (pthread_mutex_init(data->write, NULL) != 0)
		return (ft_error(data, "Error: pthread_mutex_init failed\n", i));
	if (pthread_mutex_init(data->death, NULL) != 0)
		return (ft_error(data, "Error: pthread_mutex_init failed\n", i));
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal = data->start;
		data->philos[i].left_fork = &data->forks[i];
		if (i == data->nb_philos - 1)
			data->philos[i].right_fork = &data->forks[0];
		else
			data->philos[i].right_fork = &data->forks[i + 1];
		if (pthread_create(&data->philos[i].thread_id, NULL, &philo_life,
				&data->philos[i]) != 0)
			return (ft_error(data, "Error: pthread_create failed\n",
					data->nb_philos + 1));
	}
	return (0);
}
