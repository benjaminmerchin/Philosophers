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
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&lock);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_a a;
	
	if (ac != 5 && ac != 6)
		return (ft_putstr_ret_0("Error: wrong number of arguments\n"));
	fill_struct(&a, ac, av);
	secure_values(&a);
	init_time(&a);

	//int i = 6;
	
	pthread_t newthread;
	pthread_create(&newthread, NULL, count_to_big, NULL);
	count_to_big(NULL);

	pthread_join(newthread, NULL);
	//my_turn();



	//ft_putnbr_bn(get_time_ms(&a));
	//pthread_join(&newthread, NULL);
	printf("%d\n", counter);
	return (0);
}