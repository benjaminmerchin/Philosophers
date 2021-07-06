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
