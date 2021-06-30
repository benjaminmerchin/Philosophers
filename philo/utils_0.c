#include "philosophers.h"

void	ft_putchar_buff(t_philo *philo, char c)
{
	philo->buff[philo->cursor] = c;
	philo->cursor++;
}

void	ft_putstr_buff(t_philo *philo, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar_buff(philo, str[i++]);
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

void	print_action_buffer(t_philo *philo, t_a *a, char *str)
{
	//pthread_mutex_lock(a->m_finished);
	if (a->finished == 1 || a->all_alive == 0)
		return ;
	//pthread_mutex_unlock(a->m_finished);
	ft_putnbr_buff(philo, get_time_ms(a));
	ft_putstr_buff(philo, "ms ");
	ft_putnbr_buff(philo, philo->id + 1);
	ft_putstr_buff(philo, str);
	ft_putchar_buff(philo, '\n');
	philo->buff[philo->cursor] = '\0';
	//pthread_mutex_lock(a->m_write);
	ft_putstr(philo->buff);
	//pthread_mutex_unlock(a->m_write);
	philo->cursor = 0;
}
