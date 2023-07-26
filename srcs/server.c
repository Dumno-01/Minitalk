/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:49:41 by ffreze            #+#    #+#             */
/*   Updated: 2023/07/26 21:18:27 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_info_client_pid;

void	reset_info(int *info_octet, unsigned char *info_binaire)
{
	*info_octet = 0;
	*info_binaire = 0;
	g_info_client_pid = 0;
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static int	info_octet = 0;
	static unsigned char	info_binaire = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		sig = 0;
	if (sig == SIGUSR2)
		sig = 1;
	if (g_info_client_pid != info->si_pid)
		reset_info(&info_octet, &info_binaire);
	info_binaire = info_binaire << 1 | sig;
	info_octet++;
	if (info_octet == 8 && info_binaire != 0)
	{
		write(1, &info_binaire, 1);
		reset_info(&info_octet, &info_binaire);
	}
	else if (info_octet == 8 && info_binaire == 0)
	{
		write(1, "\n", 1);
		kill(g_info_client_pid, SIGUSR2);
		reset_info(&info_octet, &info_binaire);
	}
	g_info_client_pid = info->si_pid;
	kill(g_info_client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr(getpid());
	ft_putstr("\n");
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		sleep(1);
}
