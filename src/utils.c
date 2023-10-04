/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:14:51 by ahornstr          #+#    #+#             */
/*   Updated: 2023/10/04 22:32:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	b = 1;
	c = 0;
	while ((str[a] >= 9 && str[a] <= 13) || (str[a] == ' '))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			(b *= -1);
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		c = (c * 10) + (str[a] - 48);
		a++;
	}
	return (c * b);
}

int	string_digit(char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

long int	get_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (!*s1 || !*s2)
			return (0);
		s1++;
		s2++;
	}
	return (0);
}