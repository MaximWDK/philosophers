/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:20:21 by mleonet           #+#    #+#             */
/*   Updated: 2024/02/11 11:55:54 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long int	result;
	long int	temp;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		temp = result;
		result = result * 10 + *str - '0';
		str++;
		if (temp > result && sign > 0)
			return (-1);
		else if (temp > result && sign < 0)
			return (0);
	}
	return (result * sign);
}

int	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (1);
	return (0);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time() + time;
	while (get_time() < start)
		usleep(100);
}

void	ft_print_state(t_philo *philo, char *str)
{
	if (philo->data->dead == 0)
	{
		pthread_mutex_lock(philo->data->write);
		printf("%ld %d %s\n", get_time() - philo->data->start, philo->id, str);
		pthread_mutex_unlock(philo->data->write);
	}
}

void	ft_print_simple(int id, t_data *data, char *str)
{
	pthread_mutex_lock(data->write);
	printf("%ld %d %s\n", get_time() - data->start, id, str);
	pthread_mutex_unlock(data->write);
}
