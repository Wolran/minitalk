/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:59:50 by vmuller           #+#    #+#             */
/*   Updated: 2022/11/25 12:59:50 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static int	g_flag = 0;

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
	static int	bit = 1;

	g_flag = 1;
	if (bit == 8)
	{
		write(1, "byte received\n", 14);
		bit = 0;
	}
	bit++;
	(void)sig;
}

static void	send_message(char *str, pid_t pid)
{
	size_t	i;
	size_t	j;
	int		bit;
	int		signal;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (j < 8)
		{
			bit = str[i] >> j & 1;
			g_flag = 0;
			if (bit << 1 == 0)
				signal = SIGUSR1;
			else
				signal = SIGUSR2;
			while (kill(pid, signal) != 0)
				;
			while (!g_flag)
				;
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		write(1, "ARG ERROR\n", 10);
		return (0);
	}	
	pid = ft_atoi(argv[1]);
	while (signal(SIGUSR1, ft_handler))
		;
	send_message(argv[2], pid);
	return (0);
}
