/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:59:56 by vmuller           #+#    #+#             */
/*   Updated: 2022/11/25 12:59:56 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	static int				i;
	static unsigned char	c;
	int						bit;

	(void)context;
	if (sig == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	c = c | bit << i;
	if (i == 7)
	{
		write(1, &c, 1);
		c = 0;
	}
	i = (i + 1) % 8;
	while (kill(info->si_pid, SIGUSR1))
		;
}

int	main(void)
{
	struct sigaction	data;

	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	data.sa_sigaction = ft_handler;
	data.sa_flags = SA_SIGINFO;
	sigemptyset(&data.sa_mask);
	sigaction(SIGUSR1, &data, NULL);
	sigaction(SIGUSR2, &data, NULL);
	while (1)
		pause();
	return (0);
}
