/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahornstr <ahornstr@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 14:08:55 by ahornstr      #+#    #+#                 */
/*   Updated: 2023/08/05 15:42:24 by ahornstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>

int	arg_fill(t_phil *phil, char **argv)
{
	int	i;
	
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			return (0);
		i++;
	}
	phil->arg->phil_count = ft_atoi(argv[1]);
	phil->arg->t_t_die = ft_atoi(argv[2]);
	phil->arg->t_t_eat = ft_atoi(argv[3]);
	phil->arg->t_t_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		phil->arg->a_to_eat = ft_atoi(argv[5]);
	else
		phil->arg->a_to_eat = 0;
	
	printf("count = %d\ndie = %d\neat = %d\nsleep = %d\nphilo = %d\n", phil->arg->phil_count, phil->arg->t_t_die, phil->arg->t_t_eat, phil->arg->t_t_sleep, phil->arg->a_to_eat);
	return (1);
}

void	print_two_d(char **str)
{
	int i;
	i = 0;

	while (str[i] != NULL)
	{
		printf("%s", str[i]);
		i++;
	}
}

int	struct_mem(t_phil *phil)
{
	phil->arg = malloc(sizeof(t_arg));
	if (!phil->arg)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_phil *phil;

	if (argc != 5 && argc != 6)
		return (arguments(0, NULL));
	phil = malloc(sizeof(t_phil));
	if (!phil)
		return (error("malloc struct"), 1);
	if (!struct_mem(phil))
		return (error("malloc struct"), 1);
	if (!arg_fill(phil, argv))
		return (error("arg_error"), 1);
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	printf("time = %ld\n", time);
	// if (!fork_init(phil))
	// 	return (0);
	// if (!start_living(phil))
	// 	return (error('thread_create_error'), 1);
	return (0);
}

// philo_init()
// {
// 	while(p_str[i])
// 	{
// 		philo = xxx;
// 		p_str[i] = philo;
// 		variables++;
// 		i++;
// 	}
// }