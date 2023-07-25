/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:02:21 by ffreze            #+#    #+#             */
/*   Updated: 2023/07/25 17:20:03 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_byte(char byte, int pid)
{
	int	j;

	j = 7;
	while (j >= 0)
	{
		if (byte >> j & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(500);
		j--;
	}
}

void    send_txt(char *txt, int pid)
{
    int i;
    
    i = -1;
    while (txt[++i])
		send_byte(txt[i], pid);
}

int main (int argc, char **argv)
{
    if (argc != 3)
        how_use_it();
    send_txt(argv[2], ft_atoi(argv[1]));
    return(0);
}

// penser a les gestions d'erreur du pid nombre posstif