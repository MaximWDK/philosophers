/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:23:06 by mleonet           #+#    #+#             */
/*   Updated: 2024/02/14 14:56:51 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_check_args(argc, argv) != 0)
		return (1);
	if (init_all(&data, argc, argv) != 0)
		return (2);
	if (data.nb_philos == 1)
		return (only_one(&data));
	if (create_threads(&data) != 0)
		return (3);
	ft_check_end(&data);
	if (end_threads(&data) != 0)
		return (4);
	return (0);
}

int	only_one(t_data *data)
{
	ft_print_simple(1, data, "has taken a fork");
	ft_usleep(data->time_to_die);
	ft_print_simple(1, data, "died");
	return (0);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = philo;
	if (p->id % 2 == 0)
		ft_usleep(100);
	while (p->data->dead == 0)
	{
		ft_eat(p);
		if (p->data->dead == 1)
			break ;
		ft_print_state(p, "is sleeping");
		ft_usleep(p->data->time_to_sleep);
		if (p->data->dead == 1)
			break ;
		ft_print_state(p, "is thinking");
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	philo->last_meal = get_time();
	ft_print_state(philo, "has taken a fork");
	ft_print_state(philo, "is eating");
	philo->has_eaten++;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	end_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (ft_error(data, "Error: pthread_join failed\n",
					data->nb_philos + 2));
	}
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(data->write);
	free(data->write);
	return (0);
}
