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

int	is_done(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->param->nb_philo)
	{
		if (philo->param->philo[i]->state != DONE)
			return (0);
		i++;
	}
	return (1);
	//if (philo->state != EATING /*&& philo->param->ate_at >= philo->param->t_die*/)
	//	philo->param->is_done = 1;
}

long long	actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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
		param->philo[i]->ate_at = (long long int *) actual_time;
		pthread_mutex_init(&param->philo[i]->mutex, NULL);
		i++;
	}
	return (0);
}

void	take_forks(t_philo *philo)
{
	if ((philo->id % 2))
	{	
		if (!(pthread_mutex_lock(&philo->param->mutex_forks[philo->r_fork])))
		{
			pthread_mutex_lock(&philo->param->mutex_forks[philo->l_fork]);	
			printf("%d has taken a fork\n", philo->id);
			printf("%d has taken a fork\n", philo->id);
			philo->state = READY;
		}
	}
	else if (!(philo->id % 2))
	{
		if (!(pthread_mutex_lock(&philo->param->mutex_forks[philo->l_fork])))
		{
			pthread_mutex_lock(&philo->param->mutex_forks[philo->r_fork]);	
			printf("%d has taken a fork\n", philo->id);
			printf("%d has taken a fork\n", philo->id);
			philo->state = READY;
		}
	}
}

int	eat(t_philo *philo)
{
	if (philo->state != READY)
		return (-1);
	printf("%d is eating\n", philo->id);	
	philo->state = EATING;
	usleep(philo->param->t_eat * 1000);
	philo->meals++;
	if (is_done(philo))
		return (1);
	
	return (0);
}

void	give_back_fork(t_philo *philo)
{
	if (philo->state == EATING)
	{
		printf("%d is sleeping\n", philo->id);		
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);	
		usleep(philo->param->t_sleep * 1000);		
		printf("%d is thinking\n", philo->id);
		philo->state = THINKING;
	}
}



void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(philo->param->t_eat * 1000);
	// Here need to gettimeof day + add all the conditions with taking a fork etc..
	while (is_done(philo) == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		take_forks(philo);
	//	if (eat(philo))
	//		break ;	
		
		eat(philo);
		give_back_fork(philo);
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}

int	start_to_eat(t_param *param)
{
	int	i;
//	pthread_t	thread;

	i = 0;
	gettimeofday(&param->start_at, NULL);
	while (i < param->nb_philo)
	{
		pthread_create(&param->philo[i]->thread, NULL, &routine, (void *)param->philo[i]);		
		i++;
	}
	return (0);
}

void	create_table(t_param *param)
{
	//int ret;
	
	param->philo = malloc(sizeof(t_philo *) * param->nb_philo);
	if (!param->philo)
		return ;
	if (init_philo(param))
		return ;
	start_to_eat(param);
}