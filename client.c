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

int	ft_signal(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
	return (1);
}

int	main(int arg, char **arv)
{
	int	pid;
	int	i;

	if (arg != 3)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	pid = atoi(arv[1]);
	if (pid == (0 || -1 || 1))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	i = 0;
	while (arv[2][i])
	{
		ft_signal(pid, arv[2][i]);
		i++;
	}
	return (1);
}
