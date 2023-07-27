/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:49:41 by ffreze            #+#    #+#             */
/*   Updated: 2023/07/27 14:53:21 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_info_client_pid;

static void	create_str(unsigned char c, int index)
{
	static char	*str;
	char		*temp;

	if (index == 1 && c)
	{
		if (!str)
		{
			str = malloc(sizeof(char) * 1);
			if (!str)
				exit(1);
			*str = 0;
		}
		temp = malloc(sizeof(char) * 2);
		if (!temp)
			return (free(str), exit(1));
		temp[0] = c;
		temp[1] = 0;
		str = ft_strjoin(str, temp);
	}
	else
	{
		ft_putstr_final(str);
		free(str);
		str = NULL;
	}
}

static void	reset_info(int *info_byte, unsigned char *info_binary)
{
	*info_byte = 0;
	*info_binary = 0;
	g_info_client_pid = 0;
}

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static int				info_byte = 0;
	static unsigned char	info_binary = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		sig = 0;
	if (sig == SIGUSR2)
		sig = 1;
	if (g_info_client_pid != info->si_pid)
		reset_info(&info_byte, &info_binary);
	info_binary = info_binary << 1 | sig;
	info_byte++;
	if (info_byte == 8 && info_binary != 0)
	{
		create_str(info_binary, 1);
		reset_info(&info_byte, &info_binary);
	}
	else if (info_byte == 8 && info_binary == 0)
	{
		create_str(info_binary, 2);
		kill(g_info_client_pid, SIGUSR2);
		reset_info(&info_byte, &info_binary);
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
