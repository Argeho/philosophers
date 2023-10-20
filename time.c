#include "philo.h"

long	tod(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	go_to_sleep(t_arg *arg, long ms)
{
	long	t;

	t = tod();
	while (!(arg->dead))
	{
		if (tod() - t >= ms)
			break ;
		usleep(100);
	}
}