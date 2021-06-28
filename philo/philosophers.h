#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>


typedef struct s_a {
	int	num_philo; //num philo & fork
	int time_die; //temps que le philo a apres le debut du prog, ou le debut de son dernier repas avant de mourrir
	int	time_eat; //need two fork the whole time
	int time_sleep;
	int	num_eat; //optionnal
	int limit_num_eat;

	int	start;
	int	end;
} t_a;

void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putnbr(int n);
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
int	ft_putstr_ret_0(char *s);

#endif