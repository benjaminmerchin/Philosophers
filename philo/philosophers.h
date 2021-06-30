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
	char			buff[100];
	int				cursor;
	void			*ptr;
	int				last_eat;
	int				cycles;
	int				finished;
}	t_philo;

typedef struct s_a {
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_eat;
	int					limit_num_eat;
	int					everyone_alive;

	time_t				start_sec;
	suseconds_t			start_usec;
	long unsigned int	start_usec_ms;
	int					end;

	t_philo				philo[200];

	int					finished;
}	t_a;

void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putnbr(int n);
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
int		ft_putstr_ret_0(char *s);
void	ft_putnbr_bn(int n);
void	ft_putnbr_buff_hq(t_philo *philo, int nbr);

void	print_action_buffer(t_philo *philo, t_a *a, char *str);
int		get_time_ms(t_a *a);

void	init_time(t_a *a);
void	fill_struct(t_a *a, int ac, char **av);
void	secure_values(t_a *a);
int		get_time_ms(t_a *a);
void	doing_something_for(t_a *a, int time_ms);

#endif