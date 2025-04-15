/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:50:26 by csolari           #+#    #+#             */
/*   Updated: 2025/02/05 13:22:53 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

int		ft_printf(const char *arg0, ...);
int		ft_print_putchar_fd(char c);
int		ft_print_putstr_fd(char *s);
int		ft_print_putstr_void_fd(void *s);
int		ft_print_putnbr_fd(int nbr);
int		ft_print_uns_dec(unsigned int nbr);
int		ft_print_hex(unsigned int n, char *base);
int		ft_print_putptr(unsigned long int nbr);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);

#endif