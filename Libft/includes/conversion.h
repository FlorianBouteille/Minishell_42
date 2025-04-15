/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:51:41 by csolari           #+#    #+#             */
/*   Updated: 2025/02/05 11:36:18 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSION_H
# define CONVERSION_H

int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_convert_base(unsigned long int n, char *base);
long	ft_atol(const char *nptr);

#endif