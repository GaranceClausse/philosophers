/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:35:41 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/22 09:35:41 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_param(t_param *param, char **argv)
{
	param->nb_philo = ft_atoi(argv[1]);
	param->t_die = ft_atoi(argv[2]);
	param->t_eat = ft_atoi(argv[3]);
	param->t_sleep = ft_atoi(argv[4]);
	if (argv[4])
		param->nb_meal = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_param	param;
	int		i;
	int		j;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (argv[i])
		{
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
		init_param(&param, argv);

	}
	return (0);
}