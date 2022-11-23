#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	ft_handler(int sig)
{
	if (sig == SIGUSR2)
		write(1, "The server has recived the message\n", 35);
	exit(0);
}

void	ft_signal(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((c >> i) & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(800);
		i--;
	}
}

void	send_message(int pid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		ft_signal(pid, msg[i]);
		i++;
	}
	i = 8;
	while (i > 0)
	{
		kill(pid, SIGUSR1);
		usleep(150);
		i--;
	}
}

int	main(int argc, char **argv)
{
	int		pid;

	if (argc != 3)
	{
		write(1, "ARG ERROR\n", 10);
		return (0);
	}	
	pid = ft_atoi(argv[1]);
	signal(SIGUSR2, ft_handler);
	send_message(pid, argv[2]);
	while (1)
		pause();
	return (0);
}
