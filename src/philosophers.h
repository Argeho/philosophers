/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:08:32 by ahornstr          #+#    #+#             */
/*   Updated: 2023/10/06 23:40:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define NORMAL  "\x1B[0m"
#define RED  	"\x1B[31m"
#define GREEN  	"\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  	"\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN  	"\x1B[36m"
#define WHITE  	"\x1B[37m"

typedef struct s_arg
{
	pthread_mutex_t *fork;
	pthread_mutex_t	chomp;
	pthread_mutex_t	print;
	struct s_phil	*p_structs;			
	int				phil_count;
	int				t_t_die;
	int				t_t_eat;
	int				t_t_sleep;
	int				eat_count_max;
	long long		start;
	long long		max_ate;
	int				quit;
}		t_arg;

typedef struct s_phil
{
	t_arg			*arg;
	pthread_t		philo_thread;
	int				index;
	int				left;
	int				right;
	int				eaten;
	long long		last_meal;
}		t_phil;

// main.c
int		arg_fill(t_arg *arg_temp, char **argv);

int		free_struct(t_phil *phil, t_arg *arg);

//init.c
int mutex_philo_init(t_arg *arg);
int ft_init_all(t_arg *arg, t_phil *phil);


// alg.c
void	grab_fork(t_phil *phil);
void	start_eating(t_phil *phil);
void	*alg(void *inp);
int		alive(t_arg *arg);
void	go_to_sleep(unsigned long time, t_arg *arg);
void	exit_threads(t_arg *arg);


// error.c
int		arguments(int i, char *str);
void	error(char *error_msg);


// utils.c
int		ft_atoi(const char *str);
int		string_digit(char *str);
long int	get_time(void);
void	print_status(t_phil *phil, char *status);
void	check_death(t_arg *arg, t_phil *phil);
int		ft_strcmp(const char *s1, const char *s2);


// trash
void	print_two_d(char **str);
int		struct_mem(t_phil *phil);
// mem

// time
long	tod(void);

#endif