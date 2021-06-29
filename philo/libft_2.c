#include "philosophers.h"

// void	add_buff(char c, t_a *a, int id)
// {
// 	int i;

// }

void	ft_putchar_buff(t_philo *philo, char c)
{
	philo->buff[philo->cursor] = c;
	philo->cursor++;
}

void	ft_putnbr_buff(t_philo *philo, int n)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_buff(philo, '-');
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		ft_putnbr_buff(philo, nbr / 10);
		ft_putchar_buff(philo, nbr % 10 + '0');
	}
	else
		ft_putchar_buff(philo, nbr + '0');
}

void	ft_putnbr_buff_hq(t_philo *philo, int nbr)
{
	ft_putnbr_buff(philo, nbr);
	ft_putchar_buff(philo, '\n');
	philo->buff[philo->cursor] = '\0';
	ft_putstr(philo->buff);
	philo->cursor = 0;
}
