/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:03:09 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/25 14:03:09 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_param(t_param *param, char **argv)
{
	int	i;
	
	i = 0;
	param->nb_philo = ft_atoi(argv[1]);
	param->t_die = ft_atoi(argv[2]);
	param->t_eat = ft_atoi(argv[3]);
	param->t_sleep = ft_atoi(argv[4]);
	param->nb_meal = -1;
	if (argv[5])
		param->nb_meal = ft_atoi(argv[5]);
	param->smo_dead = 0;
	param->smo_done = 0;
	pthread_mutex_init(&param->is_writing, NULL);
	param->mutex_forks = malloc(sizeof(pthread_mutex_t) * param->nb_philo);
	param->forks = malloc(sizeof(int) * param->nb_philo);
//	if (!param->mutex_forks)
//		return (ERROR);
	while (i < param->nb_philo)
	{
		pthread_mutex_init(&param->mutex_forks[i], NULL);
		param->forks[i] = 1;
		i++;
	}
}

int	check_param(t_param param)
{
	if (param.nb_philo <= 0 || param.t_die < 0 || param.t_eat < 0
		|| param.t_sleep < 0 || (param.nb_meal <= 0 && param.nb_meal != -1))
	{
		ft_putstr_fd("Invalid argument\n", 2);
		return (1);
	}
	return (0);
}

int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				ft_putstr_fd("Invalid argument\n", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}