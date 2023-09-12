/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_garbage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:58:20 by ahornstr          #+#    #+#             */
/*   Updated: 2023/06/21 12:58:44 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	get_id(t_phil *phil)
{
	int	i;
	int pos;
	int	temp;
	
	i = 0;
	pos = 1;
	phil->id = malloc(phil->arg->phil_count * sizeof(char) + 1);
	while (phil->arg->phil_count + 1 > pos)
	{
		temp = pos;
		phil->id[i] = temp + '0';
		i++;
		pos++;
	}
}