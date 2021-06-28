#include "philosophers.h"

void	fill_struct(t_a *a, int ac, char **av)
{
	a->num_philo = ft_atoi(av[1]);
	a->time_die = ft_atoi(av[2]);
	a->time_eat = ft_atoi(av[3]);
	a->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		a->num_eat = ft_atoi(av[5]);
		a->lim_num_eat = 1;
	}
	else
	{
		a->num_eat = 2147483647;
		a->lim_num_eat = 0;
	}
}

void	secure_values(t_a *a)
{
	if (a->num_philo > 200)
		exit (ft_putstr_ret_0("Error: Danger: too many philosophers\n"));
	if (a->num_philo < 0 || a->time_die < 0 || a->time_eat < 0 || a->time_sleep < 0 || a->num_eat < 0)
		exit (ft_putstr_ret_0("Error: Negative value\n"));
}

int main(int ac, char **av)
{
	t_a a;


	if (ac != 5 && ac != 6)
		return (ft_putstr_ret_0("Error: wrong number of arguments\n"));
	fill_struct(&a, ac, av);
	secure_values(&a);


	return (0);
}