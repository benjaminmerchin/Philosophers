#include "philosophers.h"

void	init_time(t_a *a)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	a->start_sec = t.tv_sec;
	a->start_usec = t.tv_usec;
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
		exit (ft_putstr_ret_0("Error: Danger: too many philosophers\n"));
	if (a->num_philo < 0 || a->time_die < 0 || a->time_eat < 0 || a->time_sleep < 0 || a->num_eat < 0)
		exit (ft_putstr_ret_0("Error: Negative value\n"));
}

int	get_time_ms(t_a *a)
{
	int time;
	struct timeval t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec - a->start_sec) * 1000 + (t.tv_usec - a->start_usec) / 1000;
	return (time);
}

void	my_turn()
{
	while (1)
	{
		sleep (1);
		printf("My turn\n");
	}
}

void	*your_turn(void *arg)
{
	int *i = (int *)arg;
	while (1)
	{
		sleep (1);
		printf("Your turn %d\n", *i);
		(*i)++;
	}
	return (NULL);
}

int counter;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t lock;
//pthread_mutex_init(&lock, NULL);

void	*count_to_big(void *arg)
{
	(void)arg;
	for (int i = 0; i < 200000; i++)
	{
		pthread_mutex_lock(&lock);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_philo *philo;
	t_a *a;

	philo = (t_philo *)arg;
	a = (t_a *)philo->ptr;
	ft_putnbr_buff_hq(philo, a->start_usec);
	
	return (NULL);
}

int main(int ac, char **av)
{
	t_a a;
	int i;

	if (ac != 5 && ac != 6)
		return (ft_putstr_ret_0("Error: wrong number of arguments\n"));
	fill_struct(&a, ac, av);
	secure_values(&a);
	init_time(&a);
	a.everyone_alive = 1;

	pthread_t newthread[200];

	i = 0;
	pthread_mutex_t fork[200];
	while (i < a.num_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}

	i = 0;
	while (i < a.num_philo)
	{
		a.philo[i].buff[0] = '\0';
		a.philo[i].cursor = 0;
		a.philo[i].id = i;
		a.philo[i].ptr = &a;
		a.philo[i].my_right_fork = &fork[i];
		if (i != a.num_philo - 1)
			a.philo[i].my_right_fork = &fork[i + 1];
		else
			a.philo[i].my_right_fork = &fork[0];
		pthread_create(&newthread[i], NULL, philo_life, &a.philo[i]);
		i++;
	}

	while (a.everyone_alive == 1)
	{
//		how_is_everyone_doing(&a);
		a.everyone_alive = 0;
	}


	//count_to_big(NULL);
	i = 0;
	while (i < a.num_philo)
	{
		pthread_join(newthread[i], NULL);
		i++;
	}
	//my_turn();


	//ft_putnbr_bn(get_time_ms(&a));
	//pthread_join(&newthread, NULL);
	printf("%d\n", counter);
	return (0);
}