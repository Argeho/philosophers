/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:08:55 by ahornstr          #+#    #+#             */
/*   Updated: 2023/09/17 12:07:28 by marvin           ###   ########.fr       */
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

// void	print_two_d(char **str)
// {
// 	int i;
// 	i = 0;

// 	while (str[i] != NULL)
// 	{
// 		printf("%s", str[i]);
// 		i++;
// 	}
// }

int	struct_mem(t_phil *phil)
{
	phil->arg = malloc(sizeof(t_arg));
	if (!phil->arg)
		return (0);
	return (1);
}

int	is_num(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(string_digit(argv[i])) || !(ft_atoi(argv[i])))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_phil *phil;

	if (argc != 5 && argc != 6)
		return (arguments(0, NULL));
	if (is_num(argv))
		return (error("please enter valid integers"), 1);
	phil = malloc(sizeof(t_phil));
	if (!phil)
		return (error("malloc struct"), 1);
	if (!struct_mem(phil))
		return (error("malloc struct"), 1);
	if (!arg_fill(phil, argv))
		return (error("arg_error"), 1);
	// if (!fork_init(phil))
	// 	return (0);
	// if (!start_living(phil))
	// 	return (error('thread_create_error'), 1);
	free_struct(phil);
	return (0);
}

int	free_struct(t_phil *phil)
{
	free(phil->arg);
	free(phil);
	return (0);
}
