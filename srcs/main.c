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

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Argument error\n", 2);
		return (1);
	}
	if (check_input(argv) == 1)
		return (1);
	memset(&param, 0, sizeof(param));
	init_param(&param, argv);
	if (check_param(param) == 1)
		return (1);
	create_table(param);
	
	return (0);
}