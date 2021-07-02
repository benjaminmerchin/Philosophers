#include "philosophers.h"

void	printf_action_buffer(t_philo *philo, t_a *a, char *str)
{
	int	i;

	pthread_mutex_lock(&a->m_stop);
	i = a->stop;
	pthread_mutex_unlock(&a->m_stop);
	if (i == 1)
		return ;
	pthread_mutex_lock(a->m_write);
	printf("%dms %d %s %d\n", get_time_ms(a), philo->id + 1, str, a->stop);
	pthread_mutex_unlock(a->m_write);
}

void	init_philo(t_a *a, int i)
{
	a->philo[i].buff[0] = '\0';
	a->philo[i].cursor = 0;
	a->philo[i].id = i;
	a->philo[i].last_eat = 0;
	a->philo[i].ptr = (void *)a;
}

int	init_main(int ac, char **av, t_a *a, int *i)
{
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_write[1];

	a->error = 0;
	if (ac != 5 && ac != 6)
	{
		ft_putstr("Error: wrong number of arguments\n");
		a->error = 1;
		return (1);
	}
	fill_struct(a, ac, av);
	secure_values(a);
	if (a->error == 1)
		return (1);
	init_time(a);
	a->stop = 0;
	*i = 0;
	pthread_mutex_init(&m_stop, NULL);
	pthread_mutex_init(&m_write[0], NULL);
	a->m_stop = m_stop;
	a->m_write = &m_write[0];
	return (0);
}
