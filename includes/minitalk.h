/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:30:21 by ffreze            #+#    #+#             */
/*   Updated: 2023/07/27 14:00:35 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

void	how_use_it(void);
int		ft_atoi(const char *str);
void	ft_putstr(char *str);
void	ft_putnbr(int n);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr_final(char *str);

#endif