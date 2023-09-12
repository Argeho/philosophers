/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:38:44 by ahornstr          #+#    #+#             */
/*   Updated: 2023/06/29 13:33:44 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	arguments(int i, char *str)
{
	if (str == NULL)
	{
		if (i == 0)
		{	
			printf("Error");
			printf("\n	\033[1;32mPlease enter 4 or 5 arguments.\033[0m\n\n");
			printf("		1. Number of philosophers\n");
			printf("		2. Time to die\n");
			printf("		3. Time to eat\n");
			printf("		4. Time to sleep\n");
			printf("	\033[1;32mOptional\033[0m\n");
			printf("		5. Number of times philosphers must eat\n");
			return (0);
		}
	}
	return (1);
}

void	error(char *error_msg)
{
	printf("Error\n%s\n", error_msg);
}

