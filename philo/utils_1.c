#include "philosophers.h"

void	init_time(t_a *a)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	a->start_sec = t.tv_sec;
	a->start_usec = t.tv_usec;
	a->start_usec_ms = a->start_sec * 1000 + a->start_usec / 1000;
}

void	fill_struct(t_a *a, int ac, char **av)
{
	a->num_philo = ft_atoi(av[1]);
	a->time_die = ft_atoi(av[2]);
	a->time_eat = ft_atoi(av[3]);
	a->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		a->num_eat = ft_atoi(av[5]);
		a->limit_num_eat = 1;
	}
	else
	{
		a->num_eat = 2147483647;
		a->limit_num_eat = 0;
	}
}

void	secure_values(t_a *a)
{
	if (a->num_philo > 200)
	{
		ft_putstr("Error: Danger: too many philosophers\n");
		a->error = 1;
	}
	if (a->num_philo < 0 || a->time_die < 0
		|| a->time_eat < 0 || a->time_sleep < 0 || a->num_eat < 0)
	{
		ft_putstr("Error: Negative value\n");
		a->error = 1;
	}
}

int	get_time_ms(t_a *a)
{
	int				time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000 - a->start_usec_ms;
	return (time);
}

void	doing_something_for(t_a *a, int time_ms)
{
	int	start;
	int	current;

	start = get_time_ms(a);
	current = start;
	while (current < start + time_ms)
	{
		usleep(100);
		current = get_time_ms(a);
	}
}
