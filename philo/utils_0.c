#include "philosophers.h"

void	printf_action_buffer(t_philo *philo, t_a *a, char *str)
{
	int	i;

	pthread_mutex_lock(&a->m_stop);
	i = a->stop;
	pthread_mutex_unlock(&a->m_stop);
	if (i == 1)
		return ;
	pthread_mutex_lock(&a->m_write);
	printf("%dms %d %s\n", get_time_ms(a), philo->id + 1, str);
	pthread_mutex_unlock(&a->m_write);
}

void	init_philo(t_a *a, int i)
{
	a->philo[i].id = i;
	a->philo[i].last_eat = 0;
	a->philo[i].ptr = (void *)a;
}

int	init_main(int ac, char **av, t_a *a)
{
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_write;

	a->error = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		a->error = 1;
		return (1);
	}
	fill_struct(a, ac, av);
	secure_values(a);
	if (a->error == 1)
		return (1);
	init_time(a);
	a->stop = 0;
	pthread_mutex_init(&m_stop, NULL);
	pthread_mutex_init(&m_write, NULL);
	a->m_stop = m_stop;
	a->m_write = m_write;
	if (a->num_philo == 1)
		return (there_is_one_philo(a));
	return (0);
}

int	there_is_one_philo(t_a *a)
{
	printf("%dms %d %s\n", get_time_ms(a), 1, "has taken a fork");
	doing_something_for(a, a->time_die);
	printf("%dms %d %s\n", get_time_ms(a), 1, "id dead");
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1 && nbr > 922337203685477580)
			return (-1);
		else if (nbr > 922337203685477580)
			return (0);
		nbr = nbr * 10 + str[i++] - '0';
	}
	return (nbr * sign);
}
