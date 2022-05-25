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

t_philo	*init_philo(t_param param, t_philo *philo, int i)
{
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i;
	philo->l_fork = 1;
	philo->r_fork = 1;
	philo->meals = 0;
	philo->state = CREATE;
	philo->param = param;
	return (philo);
}

void	create_table(t_param param)
{
	t_philo	**philo;
	int	i;

	i = param.nb_philo;
	philo = malloc(sizeof(t_philo *) * i);
	if (!philo)
		return ;
	while (i > 0)
	{
		philo[i] = init_philo(param, philo[i], i);
		printf("philo id = %d\n", philo[i]->id);
		i--;
	}
}