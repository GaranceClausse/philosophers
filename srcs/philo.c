/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:08:15 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/25 14:08:15 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	write_message(t_philo *philo, char *str)
{
	long long		timestp;
	
	timestp = actual_time();
	if (philo->param->smo_dead == 0)
	{
		printf("%lld %d %s\n", timestp, philo->id, str);
	}	
}

void	*routine(void *arg)
{
	t_philo *philo;
	long long gap;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(philo->param->t_eat * 1000);	
	philo->ate_at = (actual_time());	
	gap = actual_time() - philo->ate_at - philo->param->t_eat;
	philo->ate_at += gap;
	while (philo->param->smo_dead == 0)
	{
		if (philo->param->smo_done == philo->param->nb_philo)
			break ;
		pthread_mutex_lock(&philo->mutex);
	//	pthread_mutex_lock(&philo->param->is_writing);
		take_forks(philo);
	//	pthread_mutex_unlock(&philo->param->is_writing);
		eat(philo);
		give_back_fork(philo);
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}

void	create_table(t_param *param)
{
	int	i;

	param->philo = malloc(sizeof(t_philo *) * param->nb_philo);
	if (!param->philo)
		return ;
	if (init_philo(param))
	{
		free (param->philo);
		return ;
	}
	i = 0;	
	param->start_at = actual_time();
	while (i < param->nb_philo)
	{
		pthread_create(&param->philo[i]->thread, NULL, &routine, (void *)param->philo[i]);
		i++;
	}
}