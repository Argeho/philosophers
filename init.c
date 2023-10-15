#include "philo.h"

void	arg_fill(t_arg *arg, char **argv, int argc)
{
	pthread_mutex_init(&arg->chomp, NULL);
	pthread_mutex_init(&(arg->print), NULL);
	arg->phil_count = atoi(argv[1]);
	arg->t_t_die = atoi(argv[2]);
	arg->t_t_eat = atoi(argv[3]);
	arg->t_t_sleep = atoi(argv[4]);
	if (argc == 6)
		arg->max_eat = atoi(argv[5]);
	else
		arg->max_eat = INT_MAX;
	arg->start = tod();
	arg->dead = 0;
}

t_fork	*init_forks(int phil_count)
{
	int		i;
	t_fork	*forks;

	forks = malloc(sizeof(t_fork) * phil_count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < phil_count)
	{
		pthread_mutex_init(&(forks[i].fork), NULL);
		forks[i].free = 1;
		i++;
	}
	return (forks);
}

t_fork	*place_forks(int i, t_arg *arg, int l_or_r)
{
	if (l_or_r == 0)
	{
		if (i == arg->phil_count - 1)
			return (&(arg->forks[0]));
		else
			return (&(arg->forks[i]));
	}
	else
	{
		if (i == arg->phil_count - 1)
		{
			if (arg->phil_count == 1)
				return (NULL);
			else
				return (&(arg->forks[i]));
		}
		else
			return (&(arg->forks[i + 1]));
	}
	return (NULL);
}

t_phil	*init_philo(t_arg *arg)
{
	int		i;
	t_phil	*philos;

	i = 0;
	philos = malloc(sizeof(t_phil) * arg->phil_count);
	if (!philos)
		return (NULL);
	while (i < arg->phil_count)
	{
		philos[i].right = place_forks(i, arg, 0);
		philos[i].left = place_forks(i, arg, 1);
		philos[i].index = i + 1;
		philos[i].status = 1;
		philos[i].eaten = 0;
		philos[i].last_meal = arg->start;
		philos[i].arg = arg;
		i++;
	}
	return (philos);
}

int	check_arg(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		arg_error();
		return (1);
	}
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10 && argv[i][0] == '2')
			return (error("please enter valid integers"), 1);
		if (!(string_digit(argv[i])) || !(ft_atoi(argv[i])))
			return (error("please enter valid integers"), 1);
		i++;
	}
	return (0);
}
