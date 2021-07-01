#include "philosophers.h"

void	how_is_everyone_doing(t_a *a)
{
	int	i;
	int	time;
//	int last_eat;

	i = 0;
	time = get_time_ms(a);
	//usleep(300);
	while (i < a->num_philo/* && a->stop == 0*/)
	{
//		last_eat = a->philo[i].last_eat;
		if (a->philo[i].last_eat + a->time_die < time)
		{
			//usleep(300);
			//print_action_buffer(&(a->philo[i]), a, " is dead");
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
		i++;
	}
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_a		*a;
	int j;

	philo = (t_philo *)arg;
	a = (t_a *)philo->ptr;
	philo->cycles = 0;
	j = 0;
	while ((philo->cycles < a->num_eat || !a->limit_num_eat) && !j)
	{
		//usleep(300);
		pthread_mutex_lock(philo->my_right_fork);
		printf_action_buffer(philo, a, " has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		printf_action_buffer(philo, a, " has taken a fork");
		//printf("-%d-%d-\n", philo->id + 1, philo->cycles);


		//pthread_mutex_lock(philo->eating);
		philo->last_eat = get_time_ms(a);
		//pthread_mutex_unlock(philo->eating);

		printf_action_buffer(philo, a, " is eating");
		doing_something_for(a, a->time_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->my_right_fork);
		printf_action_buffer(philo, a, " is sleeping");
		doing_something_for(a, a->time_sleep);
		printf_action_buffer(philo, a, " is thinking");
		(philo->cycles)++;
		pthread_mutex_lock(&a->m_stop);
		j = a->stop;
		pthread_mutex_unlock(&a->m_stop);
	}
	//usleep(200);
	pthread_mutex_lock(&a->m_stop);
	if (a->stop == 0)
		a->stop = 2;
	pthread_mutex_unlock(&a->m_stop);
	return (NULL);
}

void	init_philo(t_a *a, int i)
{
	//usleep(300);
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
	// pthread_mutex_t	m_last_eat[1];	
	
	a->error = 0;
	if (ac != 5 && ac != 6)
	{
		ft_putstr_ret_0("Error: wrong number of arguments\n");
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
	// pthread_mutex_init(&m_last_eat[0], NULL);
	 a->m_stop = m_stop;
	 a->m_write = &m_write[0];
	// a->m_last_eat = &m_last_eat[0];
	return (0);
}

int	main(int ac, char **av)
{
	t_a				a;
	int				i;
	pthread_t		newthread[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	m_eating[200];

	if (init_main(ac, av, &a, &i) == 1)
		return (0);
	while (i < a.num_philo)
	{
		pthread_mutex_init(&fork[i++], NULL);
		pthread_mutex_init(&m_eating[i++], NULL);
	}
	i = 0;
	usleep(300);
	while (i < a.num_philo)
	{
		init_philo(&a, i);
		//printf("%d\n", i);
		a.philo[i].my_right_fork = &fork[i];
		a.philo[i].eating = &m_eating[i];
		if (i != a.num_philo - 1)
			a.philo[i].left_fork = &fork[i + 1];
		else
			a.philo[i].left_fork = &fork[0];
		pthread_create(&newthread[i], NULL, philo_life, &a.philo[i]);
		i = i + 2;
		if (i >= a.num_philo && i % 2 == 0)
		{
			i = 1;
			usleep(300);
		}
	}
/*	i = -1;
	while (++i < a.num_philo)
	{
		init_philo(&a, i);
		//a.philo[i].ptr = &a;
		a.philo[i].my_right_fork = &fork[i];
		if (i != a.num_philo - 1)
			a.philo[i].left_fork = &fork[i + 1];
		else
			a.philo[i].left_fork = &fork[0];
		pthread_create(&newthread[i], NULL, philo_life, &a.philo[i]);
	}*/
	while (!a.stop)
		how_is_everyone_doing(&a);
	i = 0;
	while (i < a.num_philo)
	{/*printf("-%d-\n", i + 1);*/
		pthread_join(newthread[i++], NULL);}
	return (0);
}
