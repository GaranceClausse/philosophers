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

void	take_forks(t_philo *philo)
{	
	int			first_fork;
	int			second_fork;

	check_death(philo);
	if (philo->state == DONE || philo->param->smo_dead == 1 || check_num_philo(philo))
			return ;
	first_fork = philo->l_fork;
	second_fork = philo->r_fork;
	if (!(philo->id % 2))
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	if (!(pthread_mutex_lock(&philo->param->mutex_forks[first_fork])))
	{		
		write_message(philo, "has taken a fork");		
		pthread_mutex_lock(&philo->param->mutex_forks[second_fork]);
		write_message(philo, "has taken a fork");
		philo->state = EATING;

	}	
}

void	eat(t_philo *philo)
{	
	long long	gap;

	check_death(philo);
	if (philo->state == DONE || philo->param->smo_dead == 1)
	{
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);
		return ;
	}
	philo->ate_at = (actual_time());
	write_message(philo, "is eating");
	usleep(philo->param->t_eat * 1000);
	gap = actual_time() - philo->ate_at - philo->param->t_eat;
	philo->ate_at += gap;
	philo->state = SLEEPING;	
	philo->meals++;
	if (philo->param->nb_meal != -1 && philo->meals >= philo->param->nb_meal)
	{
		philo->param->smo_done++;
		philo->state = DONE;
	}
}

void	give_back_fork(t_philo *philo)
{
	long long	gap;

	if (philo->state == SLEEPING)
	{
		write_message(philo, "is sleeping");		
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);	
		usleep(philo->param->t_sleep * 1000);
		gap = actual_time() - philo->ate_at - philo->param->t_eat - philo->param->t_eat;
		philo->ate_at += gap;
		check_death(philo);
		if (philo->param->smo_dead == 0)
			write_message(philo, "is thinking");
		usleep(1000);
		philo->state = THINKING;
	}
	else
	{
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);
		usleep(1000);
	}
}
