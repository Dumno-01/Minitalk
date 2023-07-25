/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:49:41 by ffreze            #+#    #+#             */
/*   Updated: 2023/07/25 17:20:10 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_info	c_info;

void	reset_info(void)
{
	c_info.octet = 0;
	c_info.binaire = 0;
	c_info.client_pid = 0;
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGUSR1)
		sig = 0;
	if (sig == SIGUSR2)
		sig = 1;
	if (c_info.client_pid != info->si_pid)
		reset_info();
	c_info.binaire = c_info.binaire << 1 | sig;
	c_info.octet++;
	if (c_info.octet == 8)
	{
		write(1, &c_info.binaire, 1);
		reset_info();
	}
	c_info.client_pid = info->si_pid;
}
int	main(void)
{
	struct sigaction	sa;

	reset_info();
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
// kill fonction qui envoie un signal
// sigaction et les autres fonction permettent de dire au programme comment reagir en fonction du signal envoyé/reçu, 
// (il permet d'avoir le pid du programme)
// signal fait a peu près la meme chose, c'est la meme chose en plus simple mais moins precis
// cas d'erreur : 2 client envoie un truc en meme temps, si pid est pas bon, le pid doit etre valid.