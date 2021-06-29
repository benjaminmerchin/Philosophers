#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo {
	int id;
	pthread_mutex_t *my_right_fork;
	pthread_mutex_t *left_fork;
	char	buff[100];
	int		cursor;
	void	*ptr;
}	t_philo;

typedef struct s_a {
	int	num_philo; //num philo & fork
	int time_die; //temps que le philo a apres le debut du prog, ou le debut de son dernier repas avant de mourrir
	int	time_eat; //need two fork the whole time
	int time_sleep;
	int	num_eat; //optionnal
	int limit_num_eat;
	int everyone_alive;

	time_t	start_sec; //ld
	suseconds_t start_usec; //d
	long unsigned int	start_usec_ms;
	int	end;

	t_philo philo[200];
} t_a;

// typedef struct s_tv {
// 	time_t		tv_sec;   /* seconds since Jan. 1, 1970 */
// 	suseconds_t	tv_usec;  /* and microseconds */
// } t_tv;

void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putnbr(int n);
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
int		ft_putstr_ret_0(char *s);
void	ft_putnbr_bn(int n);
void	ft_putnbr_buff_hq(t_philo *philo, int nbr);

#endif