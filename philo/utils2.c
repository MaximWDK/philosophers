/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 01:47:09 by mleonet           #+#    #+#             */
/*   Updated: 2024/02/11 01:51:46 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	is_full(t_philo *philo)
{
	if (philo->has_eaten >= philo->data->nb_meals
		&& philo->data->nb_meals != -1)
		return (1);
	return (0);
}

void	philo_dead(t_philo *philo, int dead)
{
	pthread_mutex_lock(philo->data->death);
	philo->data->dead = 1;
	if (dead == 1)
		printf("%ld %d died\n", get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(philo->data->death);
}

int	someone_dead(t_data *data)
{
	pthread_mutex_lock(data->death);
	if (data->dead)
	{
		pthread_mutex_unlock(data->death);
		return (1);
	}
	pthread_mutex_unlock(data->death);
	return (0);
}

int	ft_error(t_data *data, char *str, int i)
{
	int	j;

	j = -1;
	if (i > 0)
	{
		while (++j < i && j < data->nb_philos)
			pthread_mutex_destroy(&data->forks[j]);
	}
	if (j < i)
		pthread_mutex_destroy(data->write);
	if (j < i)
		pthread_mutex_destroy(data->death);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	if (data->death)
		pthread_mutex_destroy(data->death);
	if (data->write)
		pthread_mutex_destroy(data->write);
	printf("%s", str);
	return (-1);
}
