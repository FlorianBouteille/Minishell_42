/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:46:07 by csolari           #+#    #+#             */
/*   Updated: 2025/05/05 17:06:12 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_c_parent(int signum)
{
	(void)signum;
	g_last_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// void control_c_child()
// {

// }

// void control_c_heredoc()
// {

// }

// void control_back_parent(int signum)
// {
// 	(void)signum;
// 	rl_replace_line("minishell >", 12);
// 	return ;
// }

// void control_back_child()
// {

// }

// void control_back_heredoc()
// {
// //ne fait rien, fonction necessaire??
// }

void	signals(void)
{
	signal(SIGINT, control_c_parent);
///	signal(SIGQUIT, control_back_parent);
}
