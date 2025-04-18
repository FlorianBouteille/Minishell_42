/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:00 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/18 16:51:58 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_error(char *str, t_token **tokens)
{
	free_tokens(tokens);
	perror(str);
	exit(EXIT_FAILURE);
}
