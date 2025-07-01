/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:42:28 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/02 00:09:05 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int has_heredoc(t_data *data)
{
	if (data->type && !ft_strcmp(data->type, "HERE_DOC"))
		return (1);
	return (0);
}

void	here_doc(t_data *data)
{	
	(void)data;
	static int fd = 0;
	char *line = NULL;
	
	if (!fd)
	{
		fd = open("here_doc", O_TRUNC | O_CREAT | O_WRONLY, 0677);
		if(fd < 0)
			return ;
	}
	while((line = readline("\033[1m\033[38;5;129mheredoc → \033[0m")) != NULL)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	dup2(fd, STDIN_FILENO);
	close (fd);
}