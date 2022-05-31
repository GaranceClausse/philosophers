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

#define  _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef enum e_state {
	CREATE,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;


typedef struct s_philo
{
	int		id;
	int		l_fork;
	int		r_fork;
	int		meals;
	t_state	state;
	long long	*ate_at;
	struct s_param	*param;
}			t_philo;

typedef struct s_param
{
	int		nb_philo;	
	int		t_die;
	int		t_eat;
	int		t_sleep;	
	int		nb_meal;
	int		is_done;
	t_philo	**philo;
	pthread_mutex_t *mutex_forks;
	struct timeval	start_at;
}			t_param;


int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
void	init_param(t_param *param, char **argv);
int		check_param(t_param param);
int		check_input(char **argv);
void	create_table(t_param *param);

#endif