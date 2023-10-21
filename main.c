/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:23:41 by ahornstr          #+#    #+#             */
/*   Updated: 2023/10/17 13:35:57 by ahornstr         ###   ########.fr       */
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
		return (error("set_fork error"), 0);
	arg.forks = forks;
	philos = init_philo(&arg);
	if (!philos)
		return (error("set_philo error"), 0);
	arg.philos = (void *)philos;
	if (start_threads(&arg))
		return (1);
	free_all(&arg, philos);
	return (0);
}
