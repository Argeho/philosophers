/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:08:55 by ahornstr          #+#    #+#             */
/*   Updated: 2023/10/05 00:32:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int	arg_fill(t_arg *arg_temp, char **argv)
{
	int	i;
	
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			return (0);
		i++;
	}
	arg_temp->phil_count = ft_atoi(argv[1]);
	arg_temp->t_t_die = ft_atoi(argv[2]);
	arg_temp->t_t_eat = ft_atoi(argv[3]);
	arg_temp->t_t_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		arg_temp->eat_count_max = ft_atoi(argv[5]);
	else
		arg_temp->eat_count_max = 0;
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
		// if (argv[i] > )
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_phil *phil;
	t_arg	arg_temp;
	
	if (argc != 5 && argc != 6)
		return (arguments(0, NULL));
	if (is_num(argv))
		return (error("please enter valid integers"), 1);
	phil = malloc(sizeof(t_phil));
	if (!phil)
		return (error("malloc struct"), 1);
	if (!arg_fill(&arg_temp, argv))
		return (error("arg_error"), 1);
	if (!ft_init_all(&arg_temp, phil))
		return (0);
	if(!alive(&arg_temp))
		return (error("run error"), 1);
	free (phil);
	return (0);
}

int	free_struct(t_phil *phil, t_arg *arg)
{
	if (arg->p_structs)
		free(arg->p_structs);
	if (phil->arg)
		free(phil->arg);
	if (phil)
		free(phil);
	return (0);
}
