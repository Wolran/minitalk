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

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	i = 1;

	(void)context;
	if (sig == SIGUSR1)
		c = c | 0;
	else
		c = c | 1;
	if (i == 8)
	{
		i = 1;
		if (c == 0)
		{
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		write(1, &c, 1);
		c = 0;
		return ;
	}
	c <<= 1;
	i++;
}

int	main(void)
{
	struct sigaction	data;

	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	data.sa_sigaction = ft_handler;
	sigemptyset(&data.sa_mask);
	data.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &data, NULL);
	sigaction(SIGUSR2, &data, NULL);
	while (1)
		pause();
	return (0);
}
