/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:21:38 by mleonet           #+#    #+#             */
/*   Updated: 2024/02/11 11:42:30 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (ft_check_arg(argv[i]) != 0)
		{
			printf("Error: wrong argument(s)\n");
			return (2);
		}
	}
	return (0);
}

int	ft_check_arg(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) != 0)
			return (1);
	}
	if (ft_atoi(str) < 0)
		return (2);
	return (0);
}

void	ft_check_data(t_data *data, int argc)
{
	if (data->nb_philos < 1 || data->time_to_eat < 0 || data->time_to_die < 0
		|| data->time_to_sleep < 0 || (argc == 6 && data->nb_meals <= 0))
	{
		printf("Error: wrong argument(s)\n");
		exit (1);
	}	
}

void	ft_check_end(t_data *data)
{
	int		i;

	while (1)
	{
		data->all_ate = 0;
		i = -1;
		while (++i < data->nb_philos)
		{
			if (get_time() - data->philos[i].last_meal > data->time_to_die)
			{
				philo_dead(&data->philos[i], 1);
				break ;
			}
			if (is_full(&data->philos[i]))
				data->all_ate++;
			if (data->all_ate == data->nb_philos)
			{
				philo_dead(&data->philos[i], 0);
				break ;
			}
		}
		if (data->dead == 1)
			break ;
	}
}
