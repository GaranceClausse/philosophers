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

long long	actual_time()
{	
	struct timeval	time;

	gettimeofday(&time, NULL);	
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	is_dead(t_philo *philo)
{
	long long		timestp;
	long long		lastmeal;

	timestp = actual_time();
	lastmeal = (timestp - philo->ate_at);
	if ((lastmeal >= philo->param->t_die && philo->param->smo_dead == 0 && philo->state != EATING && philo->state != THINKING) || philo->state == DEAD)
	{
		philo->param->smo_dead = 1;
		philo->state = STARVE;
		printf("%lld %d %s (last meal = %lld)\n", timestp /*(philo->ate_at + philo->param->t_die)*/, philo->id, "is dead", lastmeal);
	}
}

void	write_message(t_philo *philo, char *str)
{
	long long		timestp;
	
	timestp = actual_time();
	if (philo->param->smo_dead == 0)
	{
		printf("%lld %d %s\n", timestp, philo->id, str);
	//	printf("%lld %d\n", lastmeal , philo->id);
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

void	take_forks(t_philo *philo)
{	
	long long	gap;
	int			first_fork;
	int			second_fork;

	is_dead(philo);
	if (philo->state == DONE || philo->param->smo_dead == 1)
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
		if (philo->param->nb_philo == 1)
		{
			pthread_mutex_unlock(&philo->param->mutex_forks[first_fork]);
			usleep(philo->param->t_die * 1000);
			gap = actual_time() - philo->ate_at - philo->param->t_die;
			philo->ate_at += gap;			
			philo->state = DEAD;
			printf ("peux pas manger avec une seule fourchette!!\n");
		}
		pthread_mutex_lock(&philo->param->mutex_forks[second_fork]);
		write_message(philo, "has taken a fork");
		write_message(philo, "has taken a fork");
		philo->state = EATING;

	}	
}

void	eat(t_philo *philo)
{	
	long long	gap;

	is_dead(philo);
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
		is_dead(philo);
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