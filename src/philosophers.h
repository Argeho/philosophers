/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahornstr <ahornstr@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 14:08:32 by ahornstr      #+#    #+#                 */
/*   Updated: 2023/08/05 15:42:52 by ahornstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <sys/time.h>

# define THINKING = 0
# define FORK = 1
# define EATING = 2
# define SLEEP = 3
# define DIED = 4

typedef struct s_arg
{
	int	phil_count;
	int	t_t_die;
	int	t_t_eat;
	int	t_t_sleep;
	int	a_to_eat;
}		t_arg;



typedef struct s_phil
{
	t_arg	*arg;
	pthread_mutex_t fork;
	pthread_t		philo;
	int		index;
	int		left;
	int		right;
}		t_phil;

// main.c
int		arg_fill(t_phil *phil, char **argv);
int	fork_init(t_phil *phil);


// alg.c
int	start_living(t_phil *phil);

// error.c
int		arguments(int i, char *str);
void	error(char *error_msg);


// utils.c
int		ft_atoi(const char *str);

// trash
void	print_two_d(char **str);
int		struct_mem(t_phil *phil);
// mem

#endif