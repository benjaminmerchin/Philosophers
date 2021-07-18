#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo {
	int				id;
	pthread_mutex_t	*my_right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*eating;
	void			*ptr;
	int				last_eat;
	int				cycles;
}	t_philo;

typedef struct s_a {
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_eat;
	int					limit_num_eat;
	int					stop;
	long unsigned int	start_usec_ms;
	int					error;

	t_philo				philo[200];
	pthread_mutex_t		m_stop;
	pthread_mutex_t		m_write;
}	t_a;

int		ft_atoi(const char *str);
int		get_time_ms(t_a *a);

void	init_time(t_a *a);
void	init_philo(t_a *a, int i);
void	fill_struct(t_a *a, int ac, char **av);
void	secure_values(t_a *a);
int		get_time_ms(t_a *a);
void	doing_something_for(t_a *a, int time_ms);
void	printf_action_buffer(t_philo *philo, t_a *a, char *str);
int		init_main(int ac, char **av, t_a *a);
int		there_is_one_philo(t_a *a);

#endif