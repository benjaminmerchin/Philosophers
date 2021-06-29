#include "philosophers.h"

int	ft_putstr_ret_0(char *s)
{
	write(1, s, ft_strlen(s));
	return (0);
}

void	ft_putnbr_bn(int n)
{
	ft_putnbr(n);
	write(1, "\n", 1);
}
