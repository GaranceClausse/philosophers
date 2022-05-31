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

void	is_done(t_philo *philo)
{
	if (philo->meals == philo->param->nb_meal)
		philo->param->is_done = 1;
	if (philo->state != EATING /*&& philo->param->ate_at >= philo->param->t_die*/)
		philo->param->is_done = 1;
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
		i++;
	}
	return (0);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->mutex_forks[philo->l_fork]);
	printf("%d has taken forks\n", philo->id);
	pthread_mutex_lock(&philo->param->mutex_forks[philo->r_fork]);
	printf("%d has taken forks\n", philo->id);
	
	
}

void	eat(t_philo *philo)
{
	usleep(philo->param->t_eat * 1000);
	philo->meals++;
	printf("%d is eating\n", philo->id);
	is_done(philo);
	pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);	
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	// Here need to gettimeof day + add all the conditions with taking a fork etc..
	while (1)
	{
		take_forks(philo);
		eat(philo);
		
		if (philo->param->is_done == 1)
			break ;
		printf("philo->param->is_done = %d,philo->meals = %d ", philo->param->is_done, philo->meals);
	}
	return (NULL);
}

int	start_to_eat(t_param *param)
{
	int	i;
	pthread_t	thread;

	i = 0;
	gettimeofday(&param->start_at, NULL);
	while (i < param->nb_philo)
	{
		pthread_create(&thread, NULL, &routine, (void *)param->philo[i]);
		pthread_join(thread, NULL);
		pthread_detach(thread);
		
	//	pthread_mutex_destroy(&param->philo[i]->mutex_left);
	//	pthread_mutex_destroy(&param->philo[i]->mutex_right);
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