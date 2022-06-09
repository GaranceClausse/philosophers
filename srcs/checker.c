/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:03:09 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/25 14:03:09 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *philo)
{
	long long		timestp;
	long long		lastmeal;

	timestp = actual_time();
	lastmeal = (timestp - philo->ate_at);
	if ((lastmeal >= philo->param->t_die && philo->param->smo_dead == 0 && philo->state != EATING
		&& philo->state != THINKING) || philo->state == DEAD)
	{
		philo->param->smo_dead = 1;
		philo->state = STARVE;
		printf("%lld %d %s (last meal = %lld)\n", (philo->ate_at + philo->param->t_die), philo->id, "is dead", lastmeal);
	}
}

int	check_num_philo(t_philo *philo)
{
	if (philo->param->nb_philo == 1)
	{
		printf("%lld 1 has taken a fork\n", philo->ate_at);	
		philo->state = DEAD;
		return (1);
	}
	return (0);
}

int	check_param(t_param param)
{
	if (param.nb_philo <= 0 || param.t_die < 0 || param.t_eat < 0
		|| param.t_sleep < 0 || (param.nb_meal <= 0 && param.nb_meal != -1))
	{
		ft_putstr_fd("Invalid argument\n", 2);
		return (1);
	}
	return (0);
}

int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				ft_putstr_fd("Invalid argument\n", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}