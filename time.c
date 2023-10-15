#include "philo.h"

long	tod(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	go_to_sleep(int ms)
{
	long			time;

	time = tod();
	while (tod() - time < ms)
		usleep(ms);
}