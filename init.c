/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahornstr <ahornstr@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 10:23:37 by ahornstr      #+#    #+#                 */
/*   Updated: 2023/10/26 18:36:49 by ahornstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_fill(t_arg *arg, char **argv, int argc)
{
	if (pthread_mutex_init(&arg->chomp, NULL))
		return (0);
	if (pthread_mutex_init(&(arg->print), NULL))
		return (0);
	arg->phil_count = ft_atoi(argv[1]);
	if (arg->phil_count > 200)
		return (error("max 200 philos plz lol"), 0);
	arg->t_t_die = ft_atoi(argv[2]);
	arg->t_t_eat = ft_atoi(argv[3]);
	arg->t_t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->max_eat = ft_atoi(argv[5]);
	else
		arg->max_eat = INT_MAX;
	arg->start = tod();
	arg->dead = 0;
	return (1);
}

int	check_arg(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		arg_error();
		return (1);
	}
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 9 && argv[i][0] != '1')
			return (error("please enter valid integers {max = 2*10^9}"), 1);
		if (!(string_digit(argv[i])) || !(ft_atoi(argv[i])))
			return (error("please enter valid integers"), 1);
		i++;
	}
	return (0);
}

t_fork	*init_forks(int phil_count)
{
	int		i;
	t_fork	*forks;

	forks = malloc(sizeof(t_fork) * phil_count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < phil_count)
	{
		if (pthread_mutex_init(&(forks[i].fork), NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

t_phil	*init_philo(t_arg *arg)
{
	int		i;
	t_phil	*philos;

	i = 0;
	philos = malloc(sizeof(t_phil) * arg->phil_count);
	if (!philos)
		return (NULL);
	while (i < arg->phil_count)
	{
		philos[i].right = &arg->forks[i];
		if (i != arg->phil_count - 1)
			philos[i].left = &arg->forks[i + 1];
		else
			philos[i].left = &arg->forks[0];
		philos[i].index = i + 1;
		philos[i].status = 1;
		philos[i].eaten = 0;
		philos[i].last_meal = arg->start;
		philos[i].arg = arg;
		i++;
	}
	return (philos);
}
