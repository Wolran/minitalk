#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	unsigned int	test;

	if (n < 0)
	{
		test = n * -1;
		ft_putchar('-');
	}
	else
		test = n;
	if (test > 9)
		ft_putnbr(test / 10);
	ft_putchar('0' + (test % 10));
}

void	ft_handler(int bit)
{
	static char				i;
	static unsigned char	c;

	c += (bit == SIGUSR1) << i;
	i++;
	if (i > 7)
	{
		write(1, &c, 1);
		c = 0;
		i = 0;
		return ;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, ft_handler);
	while (1)
		pause();
	return (0);
}
