#include "./philo.h"

int	run(t_arg *arg)
{
	t_phil	*philos;
	int		i;

	i = 0;
	philos = (t_phil *)(arg->philos);
	while (i < arg->phil_count)
	{
		if (pthread_create(&(philos[i].philo_thread), NULL, \
			&alive, &philos[i]) != 0)
			return (1);
		i++;
	}
	check_status(arg);
	i = -1;
	while (++i < arg->phil_count)
		if (pthread_join(philos[i].philo_thread, NULL) != 0)
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_phil	*philos;
	t_fork	*forks;
	
	if (check_arg(argv, argc))
		return (0);
	arg_fill(&arg, argv, argc);
	forks = init_forks(arg.phil_count);
	if (!forks)
		return (error("set_fork error"), 0);
	arg.forks = forks;
	philos = init_philo(&arg);
	if (!philos)
		return (error("set_philo error"), 0);
	arg.philos = philos;
	if (run(&arg))
		return (1);
	free_all(&arg, philos);
	return (0);
}
