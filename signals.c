/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:07:45 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 09:07:45 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_get_exit_status(130);
	}
	else if (signum == SIGQUIT)
		return ;
}

int	signal_handlers(void)
{
	struct sigaction	action;

	action = (struct sigaction){};
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	// signal(SIGQUIT, SIG_IGN);
	return (0);
}
