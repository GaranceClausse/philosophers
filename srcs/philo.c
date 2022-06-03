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


long long	actual_time(struct timeval	time)
{
	
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	is_done(t_philo *philo)
{
	int	i;
	struct timeval	time;
	long long		timestp;


	i = 0;
	gettimeofday(&time, NULL);
	timestp = (actual_time(time) - actual_time(philo->param->start_at));
	if ((timestp - philo->ate_at) >= philo->param->t_die)
	{
		philo->state = STARVE;
		philo->param->smo_dead = 1;
	}
	while (i < philo->param->nb_philo)
	{
		if (philo->param->philo[i]->state != DONE)
		{
			return (0);
		}
		if (philo->param->philo[i]->state == STARVE)
		{
			printf("Starve to death\n");
			return (1);
		}
		i++;
	}
	return (1);
	//if (philo->state != EATING /*&& philo->param->ate_at >= philo->param->t_die*/)
	//	philo->param->is_done = 1;
}



void	write_message(t_philo *philo, char *str)
{
	struct timeval	time;
	long long		timestp;

	gettimeofday(&time, NULL);
//	timestp = (actual_time(time) - actual_time(philo->param->start_at));
	timestp = actual_time(time);
	printf("%lld %d %s\n", timestp, philo->id, str);
	
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

void	take_forks(t_philo *philo)
{
	
	if (philo->state == DONE || philo->state == STARVE)
	{
		return ;
	}
	if ((philo->id % 2))
	{	
		if (!(pthread_mutex_lock(&philo->param->mutex_forks[philo->r_fork])))
		{
			pthread_mutex_lock(&philo->param->mutex_forks[philo->l_fork]);
			write_message(philo, "has taken a fork");
			write_message(philo, "has taken a fork");
			philo->state = READY;
		}
	}
	else if (!(philo->id % 2))
	{
		if (!(pthread_mutex_lock(&philo->param->mutex_forks[philo->l_fork])))
		{
			pthread_mutex_lock(&philo->param->mutex_forks[philo->r_fork]);	
			write_message(philo, "has taken a fork");
			write_message(philo, "has taken a fork");
			philo->state = READY;
		}
	}
}

int	eat(t_philo *philo)
{	
	struct timeval	time;
	if (philo->state == DONE || philo->state == STARVE)
		return (-1);

	gettimeofday(&time, NULL);
	philo->ate_at = (actual_time(time) - actual_time(philo->param->start_at));
//	printf("philo %d tmestp in eat == %lld \n", philo->id, philo->ate_at);		
	write_message(philo, "is eating");	
	philo->state = EATING;
	usleep(philo->param->t_eat * 1000);
	if (philo->param->nb_meal != -1 && philo->meals >= philo->param->nb_meal)
		philo->state = DONE;
	philo->meals++;
//	if (is_done(philo))
//		return (1);
	
	return (0);
}

void	give_back_fork(t_philo *philo)
{
	if (philo->state == EATING)
	{
		write_message(philo, "is sleeping");		
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);	
		usleep(philo->param->t_sleep * 1000);
		write_message(philo, "is thinking");	
		philo->state = THINKING;
	}
	else if (philo->state == DONE || philo->state == STARVE)
	{
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);
		//printf("Doooone\n");	
		usleep(1000);
	}
}



void	*routine(void *arg)
{
	t_philo *philo;
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo = arg;
	philo->ate_at = (actual_time(philo->param->start_at));
	if (philo->id % 2 == 0)
		usleep(philo->param->t_eat * 1000);
	// Here need to gettimeof day + add all the conditions with taking a fork etc..
	while (philo->param->smo_dead == 0 && is_done(philo) == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		take_forks(philo);
		/*if (eat(philo) == -1)
		{				
			pthread_mutex_unlock(&philo->param->mutex_forks[philo->l_fork]);
			pthread_mutex_unlock(&philo->param->mutex_forks[philo->r_fork]);
			break ;
		}*/
		eat(philo);
		give_back_fork(philo);
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}

int	start_to_eat(t_param *param)
{
	int	i;

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