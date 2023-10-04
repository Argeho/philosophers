/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:22:52 by marvin            #+#    #+#             */
/*   Updated: 2023/09/23 19:22:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	tod(void)
{
	struct timeval	time;
	long			milli;

	gettimeofday(&time, NULL);
	milli = (time.tv_sec * 1000) + (time.tv_usec * 0.001);
	return (milli);
}