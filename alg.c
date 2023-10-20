#include "philo.h"

void	check_status(t_arg *arg)
{
	int				i;

	while (!arg->full)
	{
		i = -1;
		while (++i < arg->phil_count && !arg->dead)
		{
			pthread_mutex_lock(&(arg->dead_lock));
			if (tod() - arg->philos[i].last_meal > arg->t_t_die)
			{
				print_status("died", &arg->philos[i]);
				arg->dead = 1;
			}
			pthread_mutex_unlock(&(arg->dead_lock));
			usleep(100);
		}
		if (arg->dead)
			break ;
		i = 0;
		while (arg->eat_max != -1 && i < arg->phil_count
			&& arg->philos[i].eaten >= arg->eat_max)
			i++;
		if (i == arg->phil_count)
			arg->full = 1;
	}
}

void	grab_forks( t_phil *phil, pthread_mutex_t *f_mut)
{
	pthread_mutex_lock(f_mut);
	print_status("grabbed a fork", phil);
}

void	eat(t_phil	*phil)
{
	t_arg	*arg;

	arg = phil->arg;

	grab_forks(phil, &(phil->right->fork));
	if (phil->arg->phil_count == 1)
	{
		go_to_sleep(arg, phil->arg->t_t_die);
		print_status("died", phil);
		arg->dead = 1;
		return ;
	}
	grab_forks(phil, &(phil->left->fork));
	pthread_mutex_lock(&(phil->arg->chomp));
	phil->eaten++;
	print_status("is eating", phil);
	phil->last_meal = tod();
	pthread_mutex_unlock(&(phil->arg->chomp));
	go_to_sleep(arg, phil->arg->t_t_eat);
	pthread_mutex_unlock(&(phil->right->fork));
	pthread_mutex_unlock(&(phil->left->fork));
}

void	*alive(void	*philo)
{
	t_phil	*phil;
	t_arg	*arg;

	phil = philo;
	arg = phil->arg;
	if (phil->index % 2 == 0)
		usleep(1000);
	while (!arg->dead && !arg->full)
	{
		eat(phil);
		print_status("is sleeping", phil);
		go_to_sleep(arg, phil->arg->t_t_sleep);
		print_status("is thinking", phil);
	}
	return (NULL);
}
