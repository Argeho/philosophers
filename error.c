/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:23:32 by ahornstr          #+#    #+#             */
/*   Updated: 2023/10/16 10:23:32 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	arg_error(void)
{
	printf("Error");
	printf("\n	\033[1;32mPlease enter 4 or 5 arguments.\033[0m\n\n");
	printf("		1. Number of philosophers\n");
	printf("		2. Time to die\n");
	printf("		3. Time to eat\n");
	printf("		4. Time to sleep\n");
	printf("	\033[1;32mOptional\033[0m\n");
	printf("		5. Number of times philosphers must eat\n");
}

void	error(char *error_msg)
{
		printf("Error\n%s\n", error_msg);
}

void	error_arg(t_arg	*arg, char *msg)
{
	pthread_mutex_destroy(&arg->chomp);
	pthread_mutex_destroy(&arg->print);
	error(msg);
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

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
