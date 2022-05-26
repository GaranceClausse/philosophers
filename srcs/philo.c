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
		param->philo[i]->l_fork = 1;
		param->philo[i]->r_fork = 1;
		param->philo[i]->meals = 0;
		param->philo[i]->state = CREATE;
		printf("philo id == %d\n", param->philo[i]->id);
		i++;
	}
	return (0);
}

void	*ending_condition(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (1)
	{
		printf("%d is dead\n", philo->id);
	}
	return (NULL);
}

int	start_to_eat(t_param *param)
{
	pthread_t	end;
	int	i;

	i = 0;
	while (i < param->nb_philo)
	{
		pthread_create(&end, NULL, ending_condition, (void *)param->philo[i]);
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