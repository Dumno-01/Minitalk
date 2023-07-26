/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:30:21 by ffreze            #+#    #+#             */
/*   Updated: 2023/07/26 21:18:37 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_info
{
	int		octet;
	char	binaire;
	int		client_pid;
}	t_info;

void	how_use_it(void);
void	send_byte(char byte, int pid);
void	send_txt(char *txt, int pid);
void	reset_info(int *info_octet, unsigned char *info_binaire);
void	handler(int sig, siginfo_t *info, void *ucontext);
int		ft_atoi(const char *str);
void	ft_putstr(char *str);
void	ft_putnbr(int n);

#endif