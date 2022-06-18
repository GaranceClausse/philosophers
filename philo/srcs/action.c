/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:03:37 by gclausse          #+#    #+#             */
/*   Updated: 2022/06/09 12:03:37 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, int t_usleep)
{
	long long	i;

	i = actual_time();
	pthread_mutex_lock(&philo->param->smo_dead_mutex);
	while (philo->param->smo_dead == 0)
	{
		pthread_mutex_unlock(&philo->param->smo_dead_mutex);
		check_death(philo);
		if ((actual_time() - i) >= t_usleep)
		{
			pthread_mutex_lock(&philo->param->smo_dead_mutex);
			break ;
		}
		usleep(50);
		pthread_mutex_lock(&philo->param->smo_dead_mutex);
	}
	pthread_mutex_unlock(&philo->param->smo_dead_mutex);
}

int	take_forks(t_philo *philo)
{	
	int			first_fork;
	int			second_fork;

	pthread_mutex_lock(&philo->param->smo_dead_mutex);
	if (philo->state == DONE || philo->param->smo_dead == 1
		|| check_num_philo(philo))
	{
		pthread_mutex_unlock(&philo->param->smo_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->param->smo_dead_mutex);
	first_fork = philo->l_fork;
	second_fork = philo->r_fork;
	if (!(philo->id % 2))
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	if (!(pthread_mutex_lock(&philo->param->mutex_forks[first_fork])))
	{	
		check_death(philo);
		pthread_mutex_lock(&philo->param->mutex_forks[second_fork]);
		write_message(philo, "has taken a fork");
		write_message(philo, "has taken a fork");
		philo->state = EATING;
	}
	return (0);
}

int	eat(t_philo *philo)
{	
	long long	gap;

	check_death(philo);
	if (philo->state == DONE || philo->param->smo_dead == 1)
	{
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->param->smo_dead_mutex);
	philo->ate_at = (actual_time());
	pthread_mutex_unlock(&philo->param->smo_dead_mutex);
	write_message(philo, "is eating");
	ft_usleep(philo, philo->param->t_eat);
	pthread_mutex_lock(&philo->param->smo_dead_mutex);
	gap = actual_time() - philo->ate_at - philo->param->t_eat;
	philo->ate_at += gap;
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->param->smo_dead_mutex);
	philo->meals++;
	if (philo->param->nb_meal != -1 && philo->meals >= philo->param->nb_meal)
	{
		pthread_mutex_lock(&philo->param->smo_dead_mutex);
		philo->param->smo_done++;
		philo->state = DONE;
		pthread_mutex_unlock(&philo->param->smo_dead_mutex);
	}
	return (0);
}

int	give_back_fork(t_philo *philo)
{
	long long	gap;

	check_death(philo);
	if (philo->state == SLEEPING && philo->param->smo_dead == 0)
	{
		write_message(philo, "is sleeping");
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);
		ft_usleep(philo, philo->param->t_sleep);
		pthread_mutex_lock(&philo->param->smo_dead_mutex);
		gap = actual_time() - philo->ate_at - philo->param->t_eat - philo->param->t_sleep;
		philo->ate_at += gap;
		pthread_mutex_unlock(&philo->param->smo_dead_mutex);
	//	pthread_mutex_lock(&philo->param->smo_dead_mutex);
		if (philo->param->smo_dead == 0)
			write_message(philo, "is thinking");		
		pthread_mutex_lock(&philo->param->smo_dead_mutex);
		gap = actual_time() - philo->ate_at - philo->param->t_eat - philo->param->t_sleep;
		philo->ate_at += gap;
		philo->state = THINKING;
		pthread_mutex_unlock(&philo->param->smo_dead_mutex);
	//	pthread_mutex_unlock(&philo->param->smo_dead_mutex);
		check_death(philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);
	usleep(1000);
	return (1);
}
