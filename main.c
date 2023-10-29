/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:23:41 by ahornstr          #+#    #+#             */
/*   Updated: 2023/10/29 18:29:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks( t_phil *phil, pthread_mutex_t *f_mut)
{
	pthread_mutex_lock(f_mut);
	print_status("has taken a fork", phil, 0);
}

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_phil	*philos;
	t_fork	*forks;

	if (check_arg(argv, argc))
		return (0);
	if (!arg_fill(&arg, argv, argc))
		return (0);
	forks = init_forks(arg.phil_count);
	if (!forks)
		return (error_arg(&arg, "set_fork error"), 0);
	arg.forks = forks;
	philos = init_philo(&arg);
	if (!philos)
	{
		free_all(&arg, philos);
		return (error("set_philo error"), 0);
	}
	arg.philos = (void *)philos;
	if (start_threads(&arg))
		return (free_all(&arg, philos), 0);
	free_all(&arg, philos);
	return (1);
}
