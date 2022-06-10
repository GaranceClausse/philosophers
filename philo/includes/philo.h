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
	READY,
	EATING,
	SLEEPING,
	THINKING,
	STARVE,
	DEAD,
	DONE,
}	t_state;


typedef struct s_philo
{
	int		id;
	int		cpt;
	int		l_fork;
	int		r_fork;
	int		meals;
	t_state	state;
	pthread_t	thread;
	long long	ate_at;	
	long long	interval_gap;
	struct s_param	*param;	
	pthread_mutex_t	mutex;
}			t_philo;

typedef struct s_param
{
	int		nb_philo;	
	int		t_die;
	int		t_eat;
	int		t_sleep;	
	int		nb_meal;
	int		smo_dead;
	int		smo_done;
	t_philo	**philo;
	int		*forks;
	pthread_mutex_t	is_writing;
	pthread_mutex_t *mutex_forks;
	long long	start_at;
}			t_param;


int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
long long	actual_time();

void		init_param(t_param *param, char **argv);
int			init_philo(t_param *param);
void		exit_philo(t_param *param);

int			check_param(t_param param);
int			check_input(char **argv);
int			check_num_philo(t_philo *philo);
void		check_death(t_philo *philo);

void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		give_back_fork(t_philo *philo);

void		create_table(t_param *param);
void		write_message(t_philo *philo, char *str);

#endif