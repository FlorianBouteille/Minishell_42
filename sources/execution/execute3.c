/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:43:00 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/15 09:43:03 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_stdin_stdout(t_data **data)
{
	dup2((*data)->stdin_copy, STDIN_FILENO);
	close((*data)->stdin_copy);
	dup2((*data)->stdout_copy, STDOUT_FILENO);
	close((*data)->stdout_copy);
}
