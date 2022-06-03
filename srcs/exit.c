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
	free(param->mutex_forks);
	free(param->forks);
	free(param->philo);
}