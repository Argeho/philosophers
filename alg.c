#include "philo.h"

int	check_dead(t_phil *philo)
{
	if (tod() - philo->last_meal > philo->arg->t_t_die)
	{
		philo->status = 0;
		return (0);
	}
	return (1);
}

void	check_status(t_phil *philos, t_arg *arg)
{
	int				i;

	while (!arg->dead)
	{
		i = -1;
		while (++i < arg->phil_count)
		{
			pthread_mutex_lock(&(arg->chomp));
			pthread_mutex_lock(&(arg->print));
			if (tod() - philos[i].last_meal > arg->t_t_die)
			{
				if (philos[i].eaten < arg->max_eat)
					printf("%lld ms philo    %d died\n", tod() - arg->start, philos[i].index);
				arg->dead = 1;
				pthread_mutex_unlock(&(arg->chomp));
				pthread_mutex_unlock(&(arg->print));
				break ;
			}
			pthread_mutex_unlock(&(arg->chomp));
			pthread_mutex_unlock(&(arg->print));
			go_to_sleep(1);
		}
	}
}

void	grab_forks( t_phil *phil, pthread_mutex_t *f_mut)
{
	pthread_mutex_lock(f_mut);
	print_status("grabbed a fork", phil, 0);
}

int	eat(t_phil	*phil)
{
	grab_forks(phil, &(phil->right->fork));
	if (phil->left)
	{
		grab_forks(phil, &(phil->left->fork));
		pthread_mutex_lock(&(phil->arg->chomp));
		if (phil->arg->dead)
		{
			pthread_mutex_unlock(&(phil->left->fork));
			pthread_mutex_unlock(&(phil->right->fork));
			pthread_mutex_unlock(&(phil->arg->chomp));
			return (0);
		}
		phil->eaten++;
		print_status("is eating", phil, 1);
		pthread_mutex_unlock(&(phil->arg->chomp));
		go_to_sleep(phil->arg->t_t_eat);
	}
	pthread_mutex_unlock(&(phil->right->fork));
	if (phil->left)
		pthread_mutex_unlock(&(phil->left->fork));
	return (1);
}

void	*alive(void	*philo)
{
	t_phil	*phil;

	phil = philo;
	if (phil->index % 2 == 0 && phil->arg->phil_count > 1)
		go_to_sleep(phil->arg->t_t_eat / 20);
	while (check_dead(phil) && phil->status && phil->eaten < phil->arg->max_eat)
	{
		if (!eat(phil))
			return (NULL);
		if (phil->eaten == phil->arg->max_eat)
			return (NULL);
		print_status("is sleeping", phil, 0);
		go_to_sleep(phil->arg->t_t_sleep);
		print_status("is thinking", phil, 0);
	}
	return (NULL);
}
