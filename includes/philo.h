/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:40:48 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/22 09:40:48 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
	
#include <SDL2/SDL.H>

typedef struct s_param
{
	int	nb_philo;	
	int	t_die;
	int	t_eat;
	int	t_sleep;	
	int	nb_meal;
}			t_param;

typedef struct s_philo
{
	int		id;
	int		l_fork;
	int		r_fork;
	int		meals;
	enum	state;
	t_param	param;
}			t_philo;

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
void	init_param(t_param *param, char **argv);

#endif