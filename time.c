/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:24:01 by ahornstr          #+#    #+#             */
/*   Updated: 2023/10/16 10:24:01 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	tod(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	go_to_sleep(int ms)
{
	long			time;

	time = tod();
	while (tod() - time < ms)
		usleep(200);
}

void	fork_order(t_phil *phil)
{
	long	time_to_live;

	time_to_live = phil->arg->t_t_die - (tod() - phil->last_meal);
	if (time_to_live)
		usleep(time_to_live / 10);
}
