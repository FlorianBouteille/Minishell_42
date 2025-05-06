/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:46:07 by csolari           #+#    #+#             */
/*   Updated: 2025/05/06 15:50:29 by csolari          ###   ########.fr       */
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

void control_c_heredoc()
{
	
}

void control_back_parent(int signum)
{
	(void)signum;
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	return ;
}
void	backslash(int signum)
{
	(void)signum;
	if (g_last_signal == 2)
		write(1, "\n", 1);
}
// void control_back_child()
// {

// }

// void control_back_heredoc()
// {
// //ne fait rien, fonction necessaire??

// }

// void	reset_signals(void)
// {
// 	signal(SIGQUIT, SIG_DFL);
// 	signal(SIGINT, SIG_DFL);
// }
// void	signals(void)
// {
// 	signal(SIGINT, control_c_parent);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGCHLD, backslash);
// }
