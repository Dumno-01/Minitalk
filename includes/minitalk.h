/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:30:21 by ffreze            #+#    #+#             */
/*   Updated: 2023/07/25 16:18:08 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_info
{
	int		octet;
	char	binaire;
	int		client_pid;
}	t_info;

#ifndef MINITALK_H
# define MINITALK_H
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void	how_use_it(void);
void	send_byte(char byte, int pid);
void    send_txt(char *txt, int pid);
void	reset_info(void);
void	handler(int sig, siginfo_t *info, void *ucontext);
int		ft_atoi(const char *str);
void	ft_putstr(char *str);
void	ft_putnbr(int n);

#endif