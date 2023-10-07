/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:21:31 by marvin            #+#    #+#             */
/*   Updated: 2023/09/30 17:21:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int ft_init_all(t_arg *arg, t_phil *phil)
{
	arg->p_structs = malloc(sizeof(t_phil) * arg->phil_count);
	if (!arg->p_structs)
		return (free_struct(phil, arg), 0);
	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->phil_count);
	if (!arg->fork)
		return (free_struct(phil, arg), 0);
	if (!mutex_philo_init(arg))
		return (free_struct(phil, arg), 0);
	return (1);
}

int mutex_philo_init(t_arg *arg)
{
	int	pc;

	pc = 0;

	
	while (arg->phil_count > pc)
	{
		if(pthread_mutex_init(&arg->fork[pc], NULL))
			return (0);
		pc++;
	}
	pc = 0;
	while (arg->phil_count > pc)
	{
		arg->p_structs[pc].philo_thread = 0;
		arg->p_structs[pc].index = pc;
		arg->p_structs[pc].eaten = 0;
		arg->p_structs[pc].last_meal = 0;
		arg->p_structs[pc].left = pc;
		arg->p_structs[pc].right = (pc + 1) % arg->phil_count;
		arg->p_structs[pc].arg = arg;
		pc++;
	}
	if (pthread_mutex_init(&arg->chomp, NULL) || pthread_mutex_init(&arg->print, NULL))
		return (0);
	return (1);
}

