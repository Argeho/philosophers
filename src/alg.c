/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:35:57 by ahornstr          #+#    #+#             */
/*   Updated: 2023/10/07 00:09:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// to fix: a mutex is neaded to check death. the max_ate and quit variables
// are not in mutexed. find another way pls

int	alive(t_arg *arg)
{
	int	i;

	i = -1;
	
	arg->start = tod();
	while (++i < arg->phil_count)
	{
		arg->p_structs[i].last_meal = tod();
		if (pthread_create(&arg->p_structs[i].philo_thread, NULL, alg, &(arg->p_structs[i])))
			return (0);	
	}
	check_death(arg, arg->p_structs);
	pthread_mutex_unlock(&arg->print);
	exit_threads(arg);
	return (1);
}

void	exit_threads(t_arg *arg)
{
	int	i;

	if (arg->phil_count == 1)
		pthread_detach(arg->p_structs[0].philo_thread);
	else
	{
		i = -1;
		while (++i < arg->phil_count)
		{
			pthread_join(arg->p_structs[i].philo_thread, NULL);
		}
	}
	if (arg->max_ate)
		printf(GREEN"Well... we have had enough, thanks\n"NORMAL);
	i = -1;
	while (++i < arg->phil_count)
		pthread_mutex_destroy(&arg->fork[i]);
	pthread_mutex_destroy(&arg->chomp);
	pthread_mutex_destroy(&arg->print);
	free(arg->p_structs);
	free(arg->fork);
}

void	*alg(void *inp)
{
	t_phil	*phil;
	t_arg	*arg;
	
	phil = (t_phil *)inp;
	arg = phil->arg;
	if (arg->phil_count > 1 && phil->index % 2)
		go_to_sleep(arg->t_t_eat / 50, arg);
	printf(BLUE"here quit = %d && max_ate = %lld\n"NORMAL, arg->quit, arg->max_ate);
	while (!arg->quit && !arg->max_ate)
	{
		
		// grab_fork(phil);
		start_eating(phil);
		print_status(phil, "is sleeping");
		go_to_sleep(arg->t_t_sleep, arg);
		print_status(phil, "is thinking");
	}
	return (NULL);
}

void	go_to_sleep(unsigned long time, t_arg *arg)
{
	unsigned long	sleepy;

	sleepy = tod();
	while(!arg->quit)
	{
		if (tod() - sleepy >= time)
			break ;
		usleep(arg->phil_count * 2);
	}
}

void	check_death(t_arg *arg, t_phil *phil)
{
	int	i;

	while (!arg->max_ate)
	{
		i = -1;
		while (++i < arg->phil_count && !arg->quit)
		{
			pthread_mutex_lock(&arg->chomp);
			if ((get_time() - phil[i].last_meal) >= arg->t_t_die)
			{
				print_status(&phil[i], "died");
				arg->quit = 1;
			}
			pthread_mutex_unlock(&arg->chomp);
		}
		if (arg->quit == 1)
			break ;
		i = 0;
		while (arg->eat_count_max && i < arg->phil_count && phil[i].eaten >= arg->eat_count_max)
			i++;
		arg->max_ate = (i == arg->phil_count);
	}
}

void	print_status(t_phil *phil, char *status)
{
	long	time;

	time = (tod() - phil->arg->start);
	pthread_mutex_lock(&phil->arg->print);
	if (!phil->arg->quit && !phil->arg->max_ate)
	{	
		if (ft_strcmp(status, "died") == 0)
			printf(RED"%ld %d %s\n"NORMAL, time, phil->index, status);
		else	
			printf("%ld %d %s\n", time, phil->index, status);
	}
	if (ft_strcmp(status, "died") != 0)
		pthread_mutex_unlock(&phil->arg->print);
}


void	start_eating(t_phil *phil)
{
	pthread_mutex_lock(&phil->arg->fork[phil->left]);
	print_status(phil, "has taken a fork");
	pthread_mutex_lock(&phil->arg->fork[phil->right]);
	print_status(phil, "has taken a fork");
	pthread_mutex_lock(&phil->arg->chomp);
	print_status(phil, "is eating");
	phil->last_meal = tod();
	phil->eaten++;
	pthread_mutex_unlock(&phil->arg->chomp);
	go_to_sleep(phil->arg->t_t_eat, phil->arg);
	pthread_mutex_unlock(&phil->arg->fork[phil->right]);
	pthread_mutex_unlock(&phil->arg->fork[phil->left]);
}
