#include "philo.h"

int	ft_isdigit(int c)
{
	if ((c > 47 && c < 58))
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	output;

	sign = 1;
	output = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr)
	{
		if (ft_isdigit(*nptr))
			output = output * 10 + (*nptr - 48);
		else
			return (sign * output);
		nptr++;
	}
	return (sign * output);
}

void	free_all(t_arg	*arg, t_phil *philos)
{
	int		p_count;
	int		i;
	

	p_count = arg->phil_count;
	pthread_mutex_destroy(&(arg->chomp));
	pthread_mutex_destroy(&(arg->print));
	i = -1;
	while (++i < p_count)
		pthread_mutex_destroy(&(arg->forks[i].fork));
	free(arg->forks);
	free(philos);
}

void	print_status(char *status, t_phil *philo, int type)
{
	pthread_mutex_lock(&(philo->arg->print));
	if (type == 1)
		philo->last_meal = tod();
	if (!philo->arg->dead)
		printf("%lld ms philo %-3d %s\n", tod() - philo->arg->start, philo->index, status);
	pthread_mutex_unlock(&(philo->arg->print));
}
