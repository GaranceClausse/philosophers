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
		param->philo[i]->r_fork = i + 1;
		if (i == 0)
			param->philo[i]->l_fork = param->nb_philo;
		else
			param->philo[i]->l_fork = i;
		param->philo[i]->meals = 0;
		param->philo[i]->state = CREATE;
		param->philo[i]->param = param;
		param->philo[i]->ate_at = (long long int *) actual_time;
		i++;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	
	// Here need to gettimeof day + add all the conditions with taking a fork etc..
	while (1)
	{
		pthread_mutex_lock(&philo->mutex_left);
		pthread_mutex_lock(&philo->mutex_right);
		printf("%d has taken forks\n", philo->id);
		usleep(philo->param->t_eat * 1000);
		pthread_mutex_unlock(&philo->mutex_left);
		pthread_mutex_unlock(&philo->mutex_right);
	}
	return (NULL);
}

int	start_to_eat(t_param *param)
{
	pthread_t	end;
	int	i;

	i = 0;
	gettimeofday(&param->start_at, NULL);
	while (i < param->nb_philo)
	{
		pthread_mutex_init(&param->philo[i]->mutex_left, NULL);
		pthread_mutex_init(&param->philo[i]->mutex_right, NULL);
		pthread_create(&end, NULL, routine, (void *)param->philo[i]);
		pthread_detach(end);
		/*param->philo[i]->state = EATING;
		param->philo[i]->l_fork = 0;
		param->philo[i]->r_fork = 0;
		if (param->philo[i + 1])
			param->philo[i + 1]->l_fork = 0;
		else
			param->philo[0]->l_fork = 0;
		if (param->philo[i - 1])
			param->philo[i - 1]->r_fork = 0;
		else
			param->philo[param->nb_philo - 1]->r_fork = 0;*/
	//	pthread_mutex_destroy(&param->philo[i]->mutex_left);
	//	pthread_mutex_destroy(&param->philo[i]->mutex_right);
		i++;
	}
	return (0);
}
/*
void	join_philo(t_param *param)
{
	int	i;

	i = param->nb_philo - 1;
	while (i >= 0)
	{
		pthread_join(param->philo[i]->thread, NULL);
		i--;
	}
}*/

void	create_table(t_param *param)
{
	//int ret;
	
	param->philo = malloc(sizeof(t_philo *) * param->nb_philo);
	if (!param->philo)
		return ;
	if (init_philo(param))
		return ;
	start_to_eat(param);
	
	//	if (ret) {
      //   ft_putstr_fd("Error:unable to create thread\n", 2);
        // return ;
      //	}
	//	pthread_create (pthread_t * thread, pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);
	
	//join_philo(param);
}