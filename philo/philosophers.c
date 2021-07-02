#include "philosophers.h"

void	how_is_everyone_doing(t_a *a)
{
	int	i;
	int	time;
	int	last_eat;

	i = -1;
	time = get_time_ms(a);
	while (++i < a->num_philo)
	{
		pthread_mutex_lock(a->philo[i].eating);
		last_eat = a->philo[i].last_eat;
		pthread_mutex_unlock(a->philo[i].eating);
		if (last_eat + a->time_die < time)
		{
			pthread_mutex_lock(a->m_write);
			printf("%dms %d %s\n", get_time_ms(a), i + 1, "id dead");
			pthread_mutex_unlock(a->m_write);
			pthread_mutex_lock(&a->m_stop);
			if (a->stop == 2)
				a->stop = 3;
			if (a->stop == 0)
				a->stop = 1;
			pthread_mutex_unlock(&a->m_stop);
			return ;
		}
	}
}

void	one_day_of_life(t_a *a, t_philo *philo, int *j)
{
	pthread_mutex_lock(philo->my_right_fork);
	printf_action_buffer(philo, a, " has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	printf_action_buffer(philo, a, " has taken a fork");
	pthread_mutex_lock(philo->eating);
	philo->last_eat = get_time_ms(a);
	pthread_mutex_unlock(philo->eating);
	printf_action_buffer(philo, a, " is eating");
	doing_something_for(a, a->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->my_right_fork);
	printf_action_buffer(philo, a, " is sleeping");
	doing_something_for(a, a->time_sleep);
	printf_action_buffer(philo, a, " is thinking");
	(philo->cycles)++;
	pthread_mutex_lock(&a->m_stop);
	*j = a->stop;
	pthread_mutex_unlock(&a->m_stop);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_a		*a;
	int		j;

	philo = (t_philo *)arg;
	a = (t_a *)philo->ptr;
	philo->cycles = 0;
	j = 0;
	while ((philo->cycles < a->num_eat || !a->limit_num_eat) && !j)
		one_day_of_life(a, philo, &j);
	pthread_mutex_lock(&a->m_stop);
	if (a->stop == 0)
		a->stop = 2;
	pthread_mutex_unlock(&a->m_stop);
	return (NULL);
}

void	init_mutex(t_a *a)
{
	int				i;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	m_eating[200];

	i = 0;
	while (i < a->num_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		pthread_mutex_init(&m_eating[i], NULL);
		a->philo[i].my_right_fork = &fork[i];
		a->philo[i].eating = &m_eating[i];
		if (i != a->num_philo - 1)
			a->philo[i].left_fork = &fork[i + 1];
		else
			a->philo[i].left_fork = &fork[0];
		i++;
	}
	usleep(300);
}

int	main(int ac, char **av)
{
	t_a				a;
	int				i;
	pthread_t		newthread[200];

	if (init_main(ac, av, &a) == 1)
		return (0);
	init_mutex(&a);
	i = 0;
	while (i < a.num_philo)
	{
		init_philo(&a, i);
		pthread_create(&newthread[i], NULL, philo_life, &a.philo[i]);
		i = i + 2;
		if (i >= a.num_philo && i % 2 == 0)
		{
			i = 1;
			usleep(300);
		}
	}
	while (!a.stop)
		how_is_everyone_doing(&a);
	i = 0;
	while (i < a.num_philo)
		pthread_join(newthread[i++], NULL);
	return (0);
}
