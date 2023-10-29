/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:23:26 by ahornstr          #+#    #+#             */
/*   Updated: 2023/10/16 10:23:26 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_arg *arg)
{
	t_phil	*philos;
	int		i;

	i = 0;
	philos = (t_phil *)(arg->philos);
	while (i < arg->phil_count)
	{
		if (pthread_create(&(philos[i].philo_thread), \
		NULL, &alive, &philos[i]) != 0)
		{
			while (i > 0)
			{
				pthread_join(philos[i].philo_thread, NULL);
				i--;
			}
			return (1);
		}
		i++;
	}
	check_status(philos, arg);
	i = -1;
	while (++i < arg->phil_count)
		if (pthread_join(philos[i].philo_thread, NULL) != 0)
			return (1);
	return (0);
}

int	check_dead(t_phil *philo)
{
	if (tod() - philo->last_meal > philo->arg->t_t_die)
	{
		philo->status = 0;
		return (0);
	}
	return (1);
}

void	check_status(t_phil *philos, t_arg *arg)
{
	int				i;

	while (!arg->dead && arg->phil_count != 1)
	{
		i = -1;
		while (++i < arg->phil_count)
		{
			pthread_mutex_lock(&(arg->chomp));
			pthread_mutex_lock(&(arg->print));
			if (tod() - philos[i].last_meal > arg->t_t_die)
			{
				if (philos[i].eaten < arg->max_eat)
					printf("%lld %d died\n", \
					(tod() - arg->start), philos[i].index);
				arg->dead = 1;
				pthread_mutex_unlock(&(arg->chomp));
				pthread_mutex_unlock(&(arg->print));
				break ;
			}
			pthread_mutex_unlock(&(arg->chomp));
			pthread_mutex_unlock(&(arg->print));
		}
		usleep(1000);
	}
}

int	eat(t_phil	*phil)
{
	fork_order(phil);
	grab_forks(phil, &(phil->left->fork));
	fork_order(phil);
	grab_forks(phil, &(phil->right->fork));
	pthread_mutex_lock(&(phil->arg->chomp));
	if (phil->arg->dead)
	{
		pthread_mutex_unlock(&(phil->left->fork));
		pthread_mutex_unlock(&(phil->right->fork));
		pthread_mutex_unlock(&(phil->arg->chomp));
		return (0);
	}
	phil->eaten++;
	print_status("is eating", phil, 1);
	pthread_mutex_unlock(&(phil->arg->chomp));
	go_to_sleep(phil->arg->t_t_eat);
	pthread_mutex_unlock(&(phil->right->fork));
	pthread_mutex_unlock(&(phil->left->fork));
	return (1);
}

void	*alive(void	*philo)
{
	t_phil	*phil;

	phil = philo;
	if (phil->arg->phil_count == 1)
	{
		go_to_sleep(phil->arg->t_t_die);
		print_status("died", phil, 0);
		return (NULL);
	}
	if (phil->index % 2 == 0)
	{
		print_status("is thinking", phil, 0);
		usleep(phil->arg->t_t_eat * 100);
	}
	while (check_dead(phil) && phil->status && phil->eaten < phil->arg->max_eat)
	{
		if (!eat(phil))
			return (NULL);
		if (phil->eaten == phil->arg->max_eat)
			return (NULL);
		print_status("is sleeping", phil, 0);
		go_to_sleep(phil->arg->t_t_sleep);
		print_status("is thinking", phil, 0);
	}
	return (NULL);
}
