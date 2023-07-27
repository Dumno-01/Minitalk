/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:02:21 by ffreze            #+#    #+#             */
/*   Updated: 2023/07/27 15:11:34 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_tempo;

static void	send_byte(char byte, int pid)
{
	int	j;

	j = 7;
	while (j >= 0)
	{
		g_tempo = 0;
		if (byte >> j & 1)
		{
			if (kill(pid, SIGUSR2) < 0)
				exit(1);
		}
		else
		{
			if (kill(pid, SIGUSR1) < 0)
				exit(1);
		}
		j--;
		while (g_tempo != 1)
		{
			usleep(10);
			if (kill(pid, 0) < 0)
				exit(1);
		}
	}
}

static void	send_txt(char *txt, int pid)
{
	int	i;

	i = -1;
	while (txt[++i])
		send_byte(txt[i], pid);
	send_byte(0, pid);
}

static void	listen_serv(int sig)
{
	if (sig == SIGUSR1)
		g_tempo = 1;
	else if (sig == SIGUSR2)
		write(1, "Ok\n", 3);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		how_use_it();
	signal(SIGUSR1, listen_serv);
	signal(SIGUSR2, listen_serv);
	send_txt(argv[2], ft_atoi(argv[1]));
	return (0);
}

