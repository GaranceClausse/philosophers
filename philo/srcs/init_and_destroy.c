/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:52:54 by gclausse          #+#    #+#             */
/*   Updated: 2022/06/01 11:52:54 by gclausse         ###   ########.fr       */
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

int	init_philo(t_param *param)
{
	int	i;
	
	i = 0;
	while (i < param->nb_philo)
	{
		param->philo[i] = malloc(sizeof(t_philo));
		if (!param->philo[i])
			return (1);
		param->philo[i]->id = i + 1;
		param->philo[i]->r_fork = i;
		if (i == 0)
			param->philo[i]->l_fork = param->nb_philo - 1;
		else
			param->philo[i]->l_fork = i - 1;
		param->philo[i]->meals = 0;
		param->philo[i]->state = CREATE;
		param->philo[i]->param = param;
		pthread_mutex_init(&param->philo[i]->mutex, NULL);
		i++;
	}
	return (0);
}

void	exit_philo(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_philo)
	{
		pthread_join(param->philo[i]->thread, NULL);
		pthread_mutex_destroy(&param->mutex_forks[i]);
		pthread_mutex_destroy(&param->philo[i]->mutex);
		free(param->philo[i]);
		i++;
	}
	pthread_mutex_destroy(&param->is_writing);
	free(param->mutex_forks);
	free(param->forks);
	free(param->philo);
}