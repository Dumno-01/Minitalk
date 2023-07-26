/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:02:21 by ffreze            #+#    #+#             */
/*   Updated: 2023/07/26 14:17:01 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_tempo;

void	send_byte(char byte, int pid)
{
	int	j;

	j = 7;
	while (j >= 0)
	{
		g_tempo = 0;
		if (byte >> j & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		j--;
		while (g_tempo != 1)
			usleep(10);
	}
}

void	send_txt(char *txt, int pid)
{
	int	i;

	i = -1;
	while (txt[++i])
		send_byte(txt[i], pid);
	send_byte(0, pid);
}

void	listen_serv(int sig)
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

// penser a les gestions d'erreur du pid nombre posstif