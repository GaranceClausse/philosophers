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

t_philo	*init_philo(t_param *param, int i)
{
	param->philo[i] = malloc(sizeof(t_philo));
	if (!param->philo[i])
		return (NULL);
	param->philo[i]->id = i + 1;
	param->philo[i]->l_fork = 1;
	param->philo[i]->r_fork = 1;
	param->philo[i]->meals = 0;
	param->philo[i]->state = CREATE;
	return (param->philo[i]);
}

void	*start_to_eat(void *arg)
{
	t_param *param;

	param = arg;
	param->philo[i]->state = EATING;
	param->philo[i]->l_fork = 0;
	param->philo[i]->r_fork = 0;
	if (param->philo[i + 1])
		param->philo[i + 1]->l_fork = 0;
	else
		param->philo[0]->l_fork = 0;
	if (param->philo[i - 1])
		param->philo[i - 1]->r_fork = 0;
	else
		param->philo[param->nb_philo - 1]->r_fork = 0;
	pthread_exit(NULL);
}

void	create_table(t_param *param)
{
	int ret;
	int	i;

	i = param->nb_philo - 1;
	param->philo = malloc(sizeof(t_philo *) * param->nb_philo);
	if (!param->philo)
		return ;
	while (i >= 0)
	{
		param->philo[i] = init_philo(param, i);
		printf("param philo id = %d\n", param->philo[i]->id);
		ret = pthread_create(&param->philo[i]->thread, NULL, start_to_eat, &param);
		if (ret) {
         ft_putstr_fd("Error:unable to create thread\n", 2);
         return ;
      }
	//	pthread_create (pthread_t * thread, pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);
		i--;
	}
}