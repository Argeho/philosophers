#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				free;
}					t_fork;

typedef struct s_arg
{
	void			*philos;
	t_fork			*forks;
	pthread_mutex_t	chomp;
	pthread_mutex_t	print;
	int				t_t_eat;
	int				t_t_die;
	int				t_t_sleep;
	int				phil_count;
	int				max_eat;
	int				dead;
	long long		start;
}					t_arg;

typedef struct s_philo
{
	pthread_t	philo_thread;
	t_fork		*left;
	t_fork		*right;
	int			index;
	int			status;
	int			eaten;
	long long	last_meal;
	t_arg		*arg;
}				t_phil;

int		eat(t_phil	*d);

int		check_arg(char **argv, int argc);
int		check_dead(t_phil *philo);
void	arg_fill(t_arg *data, char **argv, int argc);
int  	ft_strlen(char *s);

// Utils
void		free_all(t_arg	*data, t_phil *philos);
void		print_status(char *status, t_phil *philo, int type);
int			ft_atoi(const char *nptr);
int			ft_isspace(char c);
int			ft_isdigit(int c);

void		arg_error(void);
void		error(char *error_msg);
int			string_digit(char *str);


void	check_status(t_phil *philos, t_arg *data);
void	grab_forks( t_phil *d, pthread_mutex_t *fomutex);
void	*alive(void	*philo);
void	go_to_sleep(int ms);
long	tod(void);
t_fork	*init_forks(int num);
t_fork	*place_forks(int i, t_arg *data, int type);
t_phil	*init_philo(t_arg *data);

#endif